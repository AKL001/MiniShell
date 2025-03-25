#include "../includes/header.h"
#include <sched.h>
#include <fcntl.h>
#include <sys/wait.h>

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

int	handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		first_in;
	int		first_out;

	first_in = -1;
	first_out = -1;
	redir = cmd->redirections;
	while (redir)
	{
		if ((redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			&& handle_input_redir(redir, &first_in) == -1)
			return (-1);
		else if ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			&& handle_output_redir(redir, &first_out) == -1)
			return (-1);
		redir = redir->next;
	}
	if (first_in != -1)
    {
        if (dup2(first_in, STDIN_FILENO) == -1)
            return (error_message("dup2 failed", 1));
        close(first_in); // Close after dup2
    }
    if (first_out != -1)
    {
        if (dup2(first_out, STDOUT_FILENO) == -1)
            return (error_message("dup2 failed", 1));
        close(first_out); // Close after dup2
    }
	return (0);
}

static void	child_process_exec(t_command *cmd, t_env *env)
{
	char	*cmd_path;
	char	**args_arr;
	char	**env_arr;

	if (handle_redirections(cmd) == -1)
		exit(1);
	cmd_path = find_command_path(cmd->args->value, env);
	//  EXIT_COMMAND_NOT_FOUND 127
	if (!cmd_path)
		exit(error_message(cmd->args->value, 127));
	args_arr = args_to_array(cmd->args);
	env_arr = env_to_array(env);
	if(execve(cmd_path, args_arr, env_arr) == -1)
	{
		// EXIT_CANNOT_EXECUTE 126 
		error_message(cmd->args->value, 126);
		// printf("command not found 126\n");
		write(1, "command not found\n",18);
		free(cmd_path);
		free_array(args_arr);
		free_array(env_arr);
		exit(126);
	}
}

int	execute_simple_command(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!cmd->args)
		return (0);
	if (execute_builtin(cmd, &env))
		return (1);
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
		child_process_exec(cmd, env);
	waitpid(pid, NULL, 0);
	// if (WIFEXITED(status))
	// 	g_vars.g_exit_status = WEXITSTATUS(status);
	return (g_vars.g_exit_status);
}

int	execute_command(t_command *cmd, t_env *env)
{
	char	*cmd_path;
	char	**args_arr;
	char	**env_arr;

	if (!cmd->args)
		return (0);
	if (execute_builtin(cmd, &env))
		return (g_vars.g_exit_status);
		// return 1;
	cmd_path = find_command_path(cmd->args->value, env);
	if (!cmd_path)
	{
		error_message(cmd->args->value, 127);
		exit(127);
	}
	args_arr = args_to_array(cmd->args);
	env_arr = env_to_array(env);
	execve(cmd_path, args_arr, env_arr);
	// {
	error_message(cmd->args->value, 126);
	free(cmd_path);
	free_array(args_arr);
	free_array(env_arr);
	exit(126);
	// }
}


int	setup_pipes(t_command *cmd, int input_fd, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!cmd->next)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		return (execute_simple_command(cmd, env));
	}
	if (pipe(pipefd) == -1)
		return (error_message("pipe", 1));
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
	{
		close(pipefd[0]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (handle_redirections(cmd) == -1)
			exit(1);
		// execute_simple_command(cmd, env);
		execute_command(cmd, env);
		exit(g_vars.g_exit_status);
	}
	close(pipefd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	status = setup_pipes(cmd->next, pipefd[0], env);
	waitpid(pid, NULL, 0);
	// if (WIFEXITED(status))
	// 	g_vars.g_exit_status = WEXITSTATUS(status);
	return (g_vars.g_exit_status);
}


int	execute_command_line(t_command *cmd, t_env *env)
{
	int		stdin_copy;
	int		stdout_copy;

	if (!cmd)
		return (0);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	// multiple pipe still not working 
	if (cmd->next)
		g_vars.g_exit_status = setup_pipes(cmd, STDIN_FILENO, env);
	else
		g_vars.g_exit_status = execute_simple_command(cmd, env);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	// printf("g_exit_status => %d\n",g_vars.g_exit_status);
	// printf("\033[1;32mg_exit_status => \033[1;36m%d\033[0m\n", g_vars.g_exit_status);
	return (g_vars.g_exit_status);
}
