/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:05:05 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/09 12:05:07 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	exec_child(t_command *cmd, t_env *env, char *cmd_path)
{
	char	**args_arr;
	char	**env_arr;

	args_arr = args_to_array(cmd->args);
	env_arr = env_to_array(env);
	if (!*args_arr)
		return (0);
	execve(cmd_path, args_arr, env_arr);
	error_message("No such file or directory\n", 126);
	free(cmd_path);
	free_array(args_arr);
	free_array(env_arr);
	return (126);
}

int	execute_command(t_command *cmd, t_env *env)
{
	char	*cmd_path;

	if (handle_redirections(cmd) == -1)
		return (1);
	if (cmd->args == NULL || cmd->args->value == NULL)
		return (0);
	if (execute_builtin(cmd, &env))
		return (g_vars.g_exit_status);
	cmd_path = find_command_path(cmd->args->value, env);
	if (!cmd_path)
	{
		error_message("Command not found\n", 127);
		return (127);
	}
	return (exec_child(cmd, env, cmd_path));
}

static int	exec_last_cmd(t_command *cmd, int in_fd, pid_t *pids, int *count)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
	{
		setup_child_signals();
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		g_vars.g_exit_status = execute_command(cmd, cmd->env);
		exit(g_vars.g_exit_status);
	}
	else
	{
		pids[(*count)++] = pid;
		return (0);
	}
}

static int	exec_pipe_child(t_command *cmd, int in_fd, int pipefd[2])
{
	setup_child_signals();
	close(pipefd[0]);
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO))
			error_message("dup2", 1);
		close(in_fd);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	g_vars.g_exit_status = execute_command(cmd, cmd->env);
	exit(g_vars.g_exit_status);
}

int	setup_pipes(t_command *cmd, int in_fd, pid_t *pids, int *count)
{
	int		pipefd[2];
	pid_t	pid;

	if (!cmd->next)
		return (exec_last_cmd(cmd, in_fd, pids, count));
	if (pipe(pipefd) == -1)
		return (error_message("pipe", 1));
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
		return (exec_pipe_child(cmd, in_fd, pipefd));
	else
	{
		pids[(*count)++] = pid;
		close(pipefd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		setup_pipes(cmd->next, pipefd[0], pids, count);
		close(pipefd[0]);
	}
	return (0);
}
