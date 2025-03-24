#include "../includes/header.h"
#include <sched.h>
#include <fcntl.h>
#include <sys/wait.h>

int	handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		fd;
	int		first_in = -2, first_out = -2; // Track first input/output FDs

	redir = cmd->redirections;
	while (redir)
	{	
		if ((redir->type == REDIR_IN || redir->type == REDIR_HEREDOC) && first_in == -2)
		{
			first_in = open(redir->filename, O_RDONLY);
			if (first_in == -1)
				return (error_message(redir->filename, 1));
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT |
				((redir->type == REDIR_OUT) ? O_TRUNC : O_APPEND), 0644);
			if (fd == -1)
				return (error_message(redir->filename, 1));
			if (first_out == -2)
				first_out = fd;
			else
				close(fd);
		}
		redir = redir->next;
	}

	if (first_in != -2)
	{
		if (dup2(first_in, STDIN_FILENO) == -1)
			return (error_message("dup2 failed", 1));
		close(first_in);
	}
	if (first_out != -2)
	{
		if (dup2(first_out, STDOUT_FILENO) == -1)
			return (error_message("dup2 failed", 1));
		close(first_out);
	}
	return (0);
}



// int	handle_redirections(t_command *cmd)
// {
// 	t_redir	*redir;
// 	int		fd;
// 	int		first_in = -1, first_out = -1;

// 	redir = cmd->redirections;
// 	while (redir)
// 	{	
// 		if (redir->type == REDIR_IN && first_in == -1)
// 		{
// 			first_in = open(redir->filename, O_RDONLY);
// 			if (first_in == -1)
// 				return (error_message(redir->filename, 1));
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == REDIR_OUT)
// 		{
// 			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 				return (error_message(redir->filename, 1));
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == REDIR_APPEND)
// 		{
// 			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 				return (error_message(redir->filename, 1));
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == REDIR_HEREDOC)
// 		{
// 			fd = open(redir->filename, O_RDONLY);
// 			if (fd == -1)
// 				return (error_message(redir->filename, 1));
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 			unlink(redir->filename);
// 		}
// 		redir = redir->next;
// 	}
// 	return (0);
// }

int	execute_simple_command(t_command *cmd, t_env *env)
{
	char	*cmd_path;
	char	**args_arr;
	char	**env_arr;
	pid_t	pid;

	if (!cmd->args)
		return (0);
	if (execute_builtin(cmd, &env))
		return (1);
	pid = fork();
	if (pid == -1)
        return (error_message("fork", 1));
	if (pid == 0)
	{
		if (handle_redirections(cmd) == -1)
			exit(1);
		cmd_path = find_command_path(cmd->args->value, env);
		if (!cmd_path)
		{
			error_message(cmd->args->value, 127);
			exit(127);
		}
		args_arr = args_to_array(cmd->args);
        env_arr = env_to_array(env);
		if(execve(cmd_path, args_arr, env_arr) == -1)
			error_message(cmd->args->value, 126);
		free(cmd_path);
		free_array(args_arr);
		free_array(env_arr);
	}
	waitpid(pid, NULL, 0);
	return (g_exit_status);
}

int	execute_command_line(t_command *cmd, t_env *env)
{
	int		stdin_copy;
	int		stdout_copy;
    int     g_exit_status;

	if (!cmd)
		return (0);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	// if (cmd->next)
	// 	g_exit_status = setup_pipes(cmd, STDIN_FILENO, env);
	// else
		g_exit_status = execute_simple_command(cmd, env);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (g_exit_status);
}