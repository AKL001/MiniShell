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
#include <signal.h>

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

// int	read_heredoc(t_redir *heredoc, int *heredoc_fd, int open_fd, t_env *env)
// {
// 	int	temp_fd;

// 	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (temp_fd == -1)
// 		return (error_message("heredoc temp file", 1));
// 	if (write_heredoc_content(temp_fd, heredoc->filename, heredoc->quoted,
// 			env) == -1)
// 	{
// 		close(temp_fd);
// 		return (-1);
// 	}
// 	close(temp_fd);
// 	if (open_fd == 1)
// 	{
// 		*heredoc_fd = open(".heredoc_temp", O_RDONLY);
// 		if (*heredoc_fd == -1)
// 		{
// 			unlink(".heredoc_temp");
// 			return (error_message("heredoc read", 1));
// 		}
// 	}
// 	else
// 		*heredoc_fd = -1;
// 	unlink(".heredoc_temp");
// 	return (0);
// }

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

// int	read_heredoc(t_redir *heredoc, t_env *env)
// {
// 	int	temp_fd;

// 	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (temp_fd == -1)
// 		return (error_message("heredoc temp file open", 1));

// 	if (write_heredoc_content(temp_fd, heredoc->filename, heredoc->quoted, env) == -1)
// 	{
// 		close(temp_fd); // Clean up on error
// 		return (error_message("heredoc write failed", 1));
// 	}
// 	if (close(temp_fd) == -1)
// 		return (error_message("heredoc close failed", 1));
// 	return (0);
// }

int	read_heredoc(t_redir *heredoc, t_env *env)
{
	g_vars.g_heredoc_temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_vars.g_heredoc_temp_fd == -1)
		return (error_message("heredoc temp file open", 1));

	if (write_heredoc_content(g_vars.g_heredoc_temp_fd, heredoc->filename, heredoc->quoted, env) == -1)
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

int	read_heredoc_fork(t_redir *redir, int *heredoc_fd,int is_open, t_env *env)
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
	else
	{
		// signal(SIGINT, SIG_IGN);
		// setup_parent_signals();
		waitpid(pid, &status, 0);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_vars.g_exit_status = 130;
			*heredoc_fd = -1;
			unlink(".heredoc_temp");
			return (-1);
		}
		else if (WEXITSTATUS(status) != 0)
		{
			*heredoc_fd = -1;
			unlink(".heredoc_temp");
			return (-1);
		}
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
	}
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
				if (read_heredoc_fork(redir, &redir->heredoc_fd,open, cmd->env)
					== -1)
					return (-1);
				// printf("-----heredoc_fd in hande heredocs => %d------\n",redir->heredoc_fd);
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
