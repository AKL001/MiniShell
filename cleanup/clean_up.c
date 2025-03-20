/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:43:18 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/18 09:26:42 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_args(t_args *args)
{
	t_args	*head;

	while (args)
	{
		head = args;
		free(args->value);
		args = args->next;
		free(head);
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*head;

	while (redir)
	{
		head = redir;
		free(redir->filename);
		redir = redir->next;
		free(head);
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*head;

	while (cmd)
	{
		head = cmd;
		free_args(cmd->args);
		free_redir(cmd->redirections);
		cmd = cmd->next;
		free(head);
	}
}

void	free_token(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	if (!strings || !*strings)
		return ;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
