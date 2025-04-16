/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:37:11 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/16 21:37:12 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	handle_parent_heredoc(t_redir *redir, int *heredoc_fd, int is_open)
{
	if (is_open)
	{
		*heredoc_fd = open(".heredoc_temp", O_RDONLY);
		if (*heredoc_fd == -1)
		{
			unlink(".heredoc_temp");
			return (error_message("parent open heredoc temp failed", 1));
		}
	}
	else
		*heredoc_fd = -1;
	if (unlink(".heredoc_temp") == -1)
	{
		perror("unlink failed");
		close(*heredoc_fd);
		return (-1);
	}
	redir->heredoc_fd = *heredoc_fd;
	return (0);
}

int	read_heredoc_fork(t_redir *redir, int *heredoc_fd, int is_open, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (error_message("fork failed", 1));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		signal(SIGQUIT, SIG_IGN);
		if (read_heredoc(redir, env) == -1)
			exit(1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
	{
		g_vars.g_exit_status = WEXITSTATUS(status);
		*heredoc_fd = -1;
		unlink(".heredoc_temp");
		return (-1);
	}
	return (handle_parent_heredoc(redir, heredoc_fd, is_open));
}

void	cleanup_heredocs(t_command *cmd)
{
	t_command	*current;
	t_redir		*redir;

	current = cmd;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
