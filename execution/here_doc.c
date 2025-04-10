/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:56 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 18:59:49 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
		write(STDOUT_FILENO, "> ", 2);
		line = ft_read_until_newline(STDIN_FILENO);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
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

int	read_heredoc(t_redir *heredoc, int *heredoc_fd, int open_fd, t_env *env)
{
	int	temp_fd;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		return (error_message("heredoc temp file", 1));
	if (write_heredoc_content(temp_fd, heredoc->filename, heredoc->quoted,
			env) == -1)
	{
		close(temp_fd);
		return (-1);
	}
	close(temp_fd);
	if (open_fd == 1)
	{
		*heredoc_fd = open(".heredoc_temp", O_RDONLY);
		if (*heredoc_fd == -1)
		{
			unlink(".heredoc_temp");
			return (error_message("heredoc read", 1));
		}
	}
	else
		*heredoc_fd = -1;
	unlink(".heredoc_temp");
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
				if (read_heredoc(redir, &redir->heredoc_fd, open, cmd->env)
					== -1)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
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
