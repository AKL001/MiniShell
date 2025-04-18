/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:56 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/18 10:24:44 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <stdlib.h>

static void	process_heredoc_line(int fd, char *line, int quoted, t_env *env)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_string(line, env);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(fd, line, ft_strlen(line));
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	write_heredoc_content(int fd, char *delimiter, int quoted,
		t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(fd, line, quoted, env);
		free(line);
	}
	return (0);
}

int	read_heredoc(t_redir *heredoc, t_env *env)
{
	g_vars.g_heredoc_temp_fd = open(".heredoc_temp",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_vars.g_heredoc_temp_fd == -1)
		return (error_message("heredoc temp file open", 1));
	if (write_heredoc_content(g_vars.g_heredoc_temp_fd, heredoc->filename,
			heredoc->quoted, env) == -1)
	{
		close(g_vars.g_heredoc_temp_fd);
		g_vars.g_heredoc_temp_fd = -1;
		return (error_message("heredoc write failed", 1));
	}
	if (close(g_vars.g_heredoc_temp_fd) == -1)
		return (error_message("heredoc close failed", 1));
	g_vars.g_heredoc_temp_fd = -1;
	return (0);
}

int	handle_parent_heredoc(t_redir *redir, int *heredoc_fd, int is_open)
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

int	handle_heredocs(t_command *cmd)
{
	t_command	*current;
	t_redir		*redir;
	int			open;

	open = 0;
	current = cmd;
	while (current)
	{
		if (current->args != NULL && current->args->value != NULL)
			open = 1;
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (read_heredoc_fork(redir, &redir->heredoc_fd, open,
						*cmd->env) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}
