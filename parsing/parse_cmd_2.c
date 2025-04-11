/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:36:21 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/11 09:57:31 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_command	*initialize_command(t_command **head, t_command **tail,
		t_env *custom_env)
{
	t_command	*current_cmd;

	current_cmd = create_command();
	if (!current_cmd)
	{
		free_commands(*head);
		return (NULL);
	}
	*tail = current_cmd;
	current_cmd->env = custom_env;
	current_cmd->next = NULL;
	*tail = current_cmd;
	return (current_cmd);
}

int	handle_redirection(t_token **token, t_command *current_cmd,
		t_command *head)
{
	t_redir_type	type;

	type = get_redirection_type((*token)->type);
	*token = (*token)->next;
	if (!(*token) || (*token)->type != TOKEN_WORD)
	{
		printf("Syntax error: missing filename after redirection\n");
		free_commands(head);
		return (0);
	}
	add_command_redirection(current_cmd, type, (*token)->value);
	*token = (*token)->next;
	return (1);
}

int	handle_pipe(t_token **token, t_command *current_cmd,
		t_command *head)
{
	if (!current_cmd->args && !current_cmd->redirections)
	{
		printf("Syntax error: pipe with no command\n");
		free_commands(head);
		return (0);
	}
	*token = (*token)->next;
	if (!(*token))
	{
		printf("Syntax error: pipe with no command\n");
		free_commands(head);
		return (0);
	}
	return (1);
}

int	validate_final_command(t_command *current_cmd, t_command *head)
{
	if (current_cmd && !current_cmd->args && !current_cmd->redirections)
	{
		free_commands(head);
		return (0);
	}
	return (1);
}
