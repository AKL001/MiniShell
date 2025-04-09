/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:27 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/09 12:04:29 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	exec_single_cmd(t_command *cmd, pid_t *pids, int *count)
{
	pid_t	pid;

	if (execute_builtin(cmd, &cmd->env))
		return (g_vars.g_exit_status);
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
	{
		g_vars.g_exit_status = execute_command(cmd, cmd->env);
		exit(g_vars.g_exit_status);
	}
	else
	{
		pids[(*count)++] = pid;
		return (0);
	}
}

int	execute_command_line(t_command *cmd, t_env *env)
{
	pid_t	child_pids[100];
	int		pid_count;
	int		i;
	int		status;

	if (!cmd)
		return (0);
	cmd->env = env;
	if (handle_heredocs(cmd) == -1)
		return (cleanup_heredocs(cmd), 1);
	pid_count = 0;
	if (cmd->next)
		setup_pipes(cmd, STDIN_FILENO, child_pids, &pid_count);
	else if (exec_single_cmd(cmd, child_pids, &pid_count))
		return (cleanup_heredocs(cmd), 1);
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
