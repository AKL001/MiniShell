#include "../includes/header.h"
#include <unistd.h>

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

    while (r)
    {
        if (r->type == REDIR_HEREDOC)
        {
            if (in_fd != -1)
				close(in_fd);
            in_fd = r->heredoc_fd;
        }
        if (r->type == REDIR_IN)
		{
			if (handle_input_redir(r, &in_fd) == -1)
				return (-1);
		}
		if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
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


static int	exec_child(t_command *cmd, t_env *env, char *cmd_path)
{
	char	**args_arr;
	char	**env_arr;

	args_arr = args_to_array(cmd->args);
	env_arr = env_to_array(env);
	execve(cmd_path, args_arr, env_arr);
	printf("executed after\n");
	error_message(cmd->args->value, 126);
	free(cmd_path);
	free_array(args_arr);
	free_array(env_arr);
	return (126);
}

int	execute_command(t_command *cmd, t_env *env)
{
	char	*cmd_path;

	if (cmd->args == NULL || cmd->args->value == NULL)
        return 0;
	if (handle_redirections(cmd) == -1)
		return (1);
	if (execute_builtin(cmd, &env))
		return (g_vars.g_exit_status);
	cmd_path = find_command_path(cmd->args->value, env);
	if (!cmd_path)
	{
		error_message(cmd->args->value, 127);
		return (127);
	}
	return (exec_child(cmd, env, cmd_path));
}

static int	exec_single_cmd(t_command *cmd,t_env *env,pid_t *pids, int *count)
{
	pid_t	pid;

	
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
	{
		g_vars.g_exit_status = execute_command(cmd, env);
		exit(g_vars.g_exit_status);
	}
	else
	{
		pids[(*count)++] = pid;
		return (0);
	}
}

static int	exec_last_cmd(t_command *cmd,t_env *env,int in_fd,pid_t *pids, int *count)
{
	pid_t	pid;
	
    pid = fork();
    if (pid == -1)
        return error_message("fork", 1);
    if (pid == 0) {
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        g_vars.g_exit_status = execute_command(cmd, env);
        exit(g_vars.g_exit_status);
    }
    else
	{
		pids[(*count)++] = pid;
		return (0);
	}
}

static int	exec_pipe_child(t_command *cmd, int in_fd, int pipefd[2], t_env *env)
{
	close(pipefd[0]);
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO))
            error_message("dup2", 1);
		close(in_fd);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	g_vars.g_exit_status = execute_command(cmd, env);
	exit(g_vars.g_exit_status);
}

int	setup_pipes(t_command *cmd, int in_fd, t_env *env, pid_t *pids, int *count)
{
	int		pipefd[2];
	pid_t	pid;

	if (!cmd->next)
		return (exec_last_cmd(cmd, env, in_fd, pids, count));
	if (pipe(pipefd) == -1)
		return (error_message("pipe", 1));
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
		return (exec_pipe_child(cmd, in_fd, pipefd, env));
	else
	{
		pids[(*count)++] = pid;
		close(pipefd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		setup_pipes(cmd->next, pipefd[0], env, pids, count);
		close(pipefd[0]);
	}
	return (0);
}

int	execute_command_line(t_command *cmd, t_env *env)
{
	pid_t	child_pids[100];
	int		pid_count;
	int		i;
	int		status;

	if (!cmd)
		return (0);
    if (handle_heredocs(cmd) == -1)
        return (cleanup_heredocs(cmd),1);
	pid_count = 0;
	if (cmd->next)
		setup_pipes(cmd, STDIN_FILENO, env, child_pids, &pid_count);
	else if (exec_single_cmd(cmd, env, child_pids, &pid_count))
		return (cleanup_heredocs(cmd),1);
	i = -1;
	while (++i < pid_count)
	{
		waitpid(child_pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars.g_exit_status = WEXITSTATUS(status);
	}
    cleanup_heredocs(cmd);
	
	return (g_vars.g_exit_status);
}
