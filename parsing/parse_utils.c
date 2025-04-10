/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:28:49 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/18 02:15:18 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_quoted_and_strip(char **str)
{
	size_t	len;
	char	*original = *str;
	char	*new_str;

	len = strlen(original);
	if (len >= 2 && (
			(original[0] == '\'' && original[len - 1] == '\'') ||
			(original[0] == '"' && original[len - 1] == '"')))
	{
		new_str = ft_strndup(original + 1, len - 2);
		free(*str);
		*str = new_str;
		return 1;
	}
	return 0;
}

void	add_command_redirection(t_command *cmd, t_redir_type type, char *filename)
{
	t_redir	*redir;
	char	*fname_copy;

	fname_copy = ft_strdup(filename);
	if (!fname_copy)
		return ;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;

	redir->quoted = is_quoted_and_strip(&fname_copy);
	redir->type = type;
	// redir->heredoc_fd = -1;
	redir->next = cmd->redirections;
	cmd->redirections = redir;

	if (!redir->quoted && expand_string(fname_copy, cmd->env) != NULL)
	{
		redir->filename = expand_string(fname_copy, cmd->env);
	}
	else
		redir->filename = ft_strdup(fname_copy);
	free(fname_copy);
}

// void	add_command_redirection(t_command *cmd, t_redir_type type,
// 		char *filename)
// {
// 	t_redir	*redir;

	
// 	redir = malloc(sizeof(t_redir));
// 	redir->filename = ft_strdup(filename);
// 	// ft_strdup(filename)
// 	redir->type = type;
// 	redir->next = cmd->redirections;
// 	cmd->redirections = redir;
// }

void	add_command_args(t_command *cmd, char *value)
{
	t_args	*args;
	t_args	*head;

	if (!value)
		return ;
	args = malloc(sizeof(t_args));
	if (!args)
		return ;
	args->value = ft_strdup(value);
	args->next = NULL;
	if (!cmd->args)
		cmd->args = args;
	else
	{
		head = cmd->args;
		while (head->next)
			head = head->next;
		head->next = args;
	}
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->env = NULL;
	cmd->redirections = NULL;
	return (cmd);
}
