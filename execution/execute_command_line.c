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
#include <unistd.h>

static void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_vars.g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_vars.g_exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit\n", 1);
			g_vars.g_exit_status = 131;
		}
	}
}

static void	restore_std_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}

static int	restore_and_exit(int saved_fds[2], int exit_code)
{
	restore_std_fds(saved_fds);
	return (exit_code);
}

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args->value)
		return (0);
	return (
		ft_strcmp(cmd->args->value, "cd") == 0 ||
		ft_strcmp(cmd->args->value, "echo") == 0 ||
		ft_strcmp(cmd->args->value, "env") == 0 ||
		ft_strcmp(cmd->args->value, "exit") == 0 ||
		ft_strcmp(cmd->args->value, "export") == 0 ||
		ft_strcmp(cmd->args->value, "pwd") == 0 ||
		ft_strcmp(cmd->args->value, "unset") == 0
	);
}

int	exec_single_cmd(t_command *cmd, pid_t *pids, int *count)
{
	pid_t	pid;
	int		p_fds[2];

	p_fds[0] = dup(STDIN_FILENO);
	p_fds[1] = dup(STDOUT_FILENO);
	if (is_builtin(cmd))
	{
		if (handle_redirections(cmd) == -1)
			return (restore_and_exit(p_fds, 1));
		if (execute_builtin(cmd, &cmd->env))
			return (restore_and_exit(p_fds, 1));
		restore_std_fds(p_fds);
		return (0);
	}
	restore_std_fds(p_fds);
	// printf("exec single cmd\n");
	pid = fork();
	if (pid == -1)
		return (error_message("fork", 1));
	if (pid == 0)
	{
		setup_child_signals();
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
	// printf("heredoc fd = %d\n",cmd->redirections->heredoc_fd);
	if (cmd->next)
		setup_pipes(cmd, STDIN_FILENO, child_pids, &pid_count);
	else if (exec_single_cmd(cmd, child_pids, &pid_count))
		return (cleanup_heredocs(cmd), 1);
	i = -1;
	while (++i < pid_count)
	{
		waitpid(child_pids[i], &status, 0);
		handle_exit_status(status);
	}
	cleanup_heredocs(cmd);
	return (g_vars.g_exit_status);
}
