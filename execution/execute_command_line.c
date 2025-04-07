#include "../includes/header.h"


static int	handle_input_redir(t_redir *redir, int *first_in)
{
	if (*first_in != -1)
		return (0);
	*first_in = open(redir->filename, O_RDONLY);
	if (*first_in == -1)
		return (error_message(redir->filename, 1));
	return (0);
}

static int	handle_output_redir(t_redir *redir, int *first_out)
{
	int	fd;
	int	flags;

	// if (*first_out != -1)
	// 	close(*first_out);
	flags = O_WRONLY | O_CREAT;
	if (redir->type == REDIR_OUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd = open(redir->filename, flags, 0644);
	if (fd == -1)
		return (error_message(redir->filename, 1));
	if (*first_out == -1)
		*first_out = fd;
	else
		close(fd);
	return (0);
}

int handle_redirections(t_command *cmd)
{
    t_redir *r = cmd->redirections;
    int in_fd = -1;
    int out_fd = -1;
	// printf("*****handle redir called*****\n");
    while (r)
    {
        if (r->type == REDIR_HEREDOC)
        {
            if (in_fd != -1) close(in_fd);
            in_fd = r->heredoc_fd;
        }
        if (r->type == REDIR_IN)
		{
			if (handle_input_redir(r, &in_fd) == -1)
				return (-1);
		}
		else if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
		{
			if (handle_output_redir(r, &out_fd) == -1)
				return (-1);
		}
        r = r->next;
    }

    if (in_fd != -1) dup2(in_fd, STDIN_FILENO);
    if (out_fd != -1) dup2(out_fd, STDOUT_FILENO);
    
    if (in_fd != -1) close(in_fd);
    if (out_fd != -1) close(out_fd);
    
    return 0;
}

int	execute_command(t_command *cmd, t_env *env)
{
	char	*cmd_path;
	char	**args_arr;
	char	**env_arr;

	// if (!cmd->args)
	// 	return (0);
	if (handle_redirections(cmd) == -1)
		exit(1);
	if (execute_builtin(cmd, &env))
		return (1);
	cmd_path = find_command_path(cmd->args->value, env);
	if (!cmd_path)
	{
		// Command not found 127
		error_message(cmd->args->value, 127);
		exit(127);
	}
	args_arr = args_to_array(cmd->args);
	// env_arr = env_to_array(env);
	if (execve(cmd_path, args_arr, env_to_array(env)) == -1)
	{
		error_message(cmd->args->value, 126);
		free(cmd_path);
		free_array(args_arr);
		free_array(env_arr);
		exit(126);
	}
	return 0;
}
int setup_pipes(t_command *cmd, int input_fd, t_env *env, pid_t *child_pids, int *pid_count) {
    int pipefd[2];
    pid_t pid;

    if (!cmd->next) {
        pid = fork();
        if (pid == -1)
            return error_message("fork", 1);
        if (pid == 0) {
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            execute_command(cmd, env);
			exit(1);
        } else {
            child_pids[(*pid_count)++] = pid;
            if (input_fd != STDIN_FILENO)
                close(input_fd);
            return 0;
        }
    }
    if (pipe(pipefd) == -1)
        return error_message("pipe", 1);

    pid = fork();
    if (pid == -1)
        return error_message("fork", 1);

    if (pid == 0) {
        close(pipefd[0]);
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_command(cmd, env);
		exit(1);
    } else {
        child_pids[(*pid_count)++] = pid;
        close(pipefd[1]);
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        setup_pipes(cmd->next, pipefd[0], env, child_pids, pid_count);
        close(pipefd[0]);
    }
    return 0;
}

int execute_command_line(t_command *cmd, t_env *env) {
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);
    pid_t child_pids[100];
    int pid_count = 0;
    int i;
    int status;
	t_redir *redir;
	t_command *current;
    if (!cmd)
        return 0;

	// redir = cmd->redirections;
	// while (redir)
	// {
	// 	if (redir->type == REDIR_HEREDOC)
	// 	{
	// 		if (read_heredoc(redir, &redir->heredoc_fd) == -1)
	// 		{
	// 			close(stdin_copy);
	// 			close(stdout_copy);
	// 			return 1;
	// 		}
	// 	}
	// 	redir = redir->next;
	// }
	current = cmd;
    while (current) {
        redir = current->redirections;
        while (redir) {
            if (redir->type == REDIR_HEREDOC) {
                if (read_heredoc(redir, &redir->heredoc_fd) == -1) {
                    close(stdin_copy);
                    close(stdout_copy);
                    return 1;
                }
            }
            redir = redir->next;
        }
        current = current->next;
    }
	// handle_redirections(cmd);
		// return (0);
    if (cmd->next)
	{
		// printf("multiple pipe execution\n");
		// printf("\033[0;34mmultiple pipe execution\033[0m\n");
        setup_pipes(cmd, STDIN_FILENO, env, child_pids, &pid_count);
	}
	else
	{
		// printf("single command execution\n");
		// printf("\033[0;33mSingle command execution\033[0m\n");
        pid_t pid = fork();
        if (pid == -1)
            return error_message("fork", 1);
        if (pid == 0) {
            execute_command(cmd, env);
        } else {
            child_pids[pid_count++] = pid;
        }
    }
    i = -1;
    while(++i < pid_count)
    {
        waitpid(child_pids[i], &status, 0);
        if (WIFEXITED(status))
            g_vars.g_exit_status = WEXITSTATUS(status);
    }
    
	current = cmd;
    while (current) {
        redir = current->redirections;
        while (redir) {
            if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1) {
                close(redir->heredoc_fd);
                redir->heredoc_fd = -1; // Mark as closed
            }
            redir = redir->next;
        }
        current = current->next;
    }
	// Close all heredoc file descriptors
    // redir = cmd->redirections;
    // while (redir)
    // {
    //     if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
	// 	{
	// 		printf("-----fd before close = %d\n",redir->heredoc_fd);	
    //         close(redir->heredoc_fd);
	// 	}
    //     redir = redir->next;
    // }
    // Clean up temporary heredoc file
    // unlink(".heredoc_temp");
    
    // Restore stdin/stdout
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
    
    // printf("\033[1;32mg_exit_status => \033[1;36m%d\033[0m\n", g_vars.g_exit_status);
    return g_vars.g_exit_status;
}

