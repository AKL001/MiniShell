/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:11:14 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 19:11:16 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <signal.h>

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_vars.in_child == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_vars.g_exit_status = 130;
	}
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;

	if (g_vars.g_heredoc_temp_fd != -1)
	{
		close(g_vars.g_heredoc_temp_fd);
		g_vars.g_heredoc_temp_fd = -1;
	}

	unlink(".heredoc_temp");
	write(1, "\n", 1);
	g_vars.g_exit_status = 130;
	exit(130);
}

void	setup_parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	handle_child_signals(int sig_num)
{
	if (sig_num == 2)
		g_vars.g_exit_status = 130;
	else
	{
		ft_putstr_fd("Quit", 1);
		g_vars.g_exit_status = 131;
	}
	write(1, "\n", 1);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
