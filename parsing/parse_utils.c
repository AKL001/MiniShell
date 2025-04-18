/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:28:49 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/18 10:34:24 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	add_command_redirection(t_command *cmd, t_redir_type type,
		char *filename)
{
	t_redir	*redir;
	t_redir	*last;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	remply_redir(&redir, filename, type);
	redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

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
