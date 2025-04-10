/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:13:49 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:45:39 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_command	*parse_token(t_token *token, t_env *custom_env)
{
	t_command		*current_cmd;
	t_command		*head;
	t_command		**tail;
	t_redir_type	type;
	t_token			*head_token;

	current_cmd = NULL;
	head = NULL;
	tail = &head;
	head_token = token;
	while (token)
	{
		if (!current_cmd)
		{
			current_cmd = create_command();
			if (!current_cmd)
			{
				free_commands(head);
				return (NULL);
			}
			*tail = current_cmd;
			current_cmd->env = custom_env;
			tail = &current_cmd->next;
		}
		if (is_redirection(token->type))
		{
			type = get_redirection_type(token->type);
			token = token->next;
			if (!token || token->type != TOKEN_WORD)
			{
				printf("Syntax error: missing filename after redirection\n");
				free_commands(head);
				return (NULL);
			}
			add_command_redirection(current_cmd, type, token->value);
			token = token->next;
		}
		else if (token->type == TOKEN_PIPE)
		{
			if ((!current_cmd->args && !current_cmd->redirections))
			{
				printf("Syntax error: pipe with no command\n");
				free_commands(head);
				return (NULL);
			}
			current_cmd = NULL;
			token = token->next;
			if (!token)
			{
				printf("Syntax error: pipe with no command\n");
				free_commands(head);
				return (NULL);
			}
		}
		else if (token->type == TOKEN_WORD)
		{
			add_command_args(current_cmd, token->value);
			token = token->next;
		}
		else
		{
			free_commands(head);
			return (NULL);
		}
	}
	if (current_cmd && !current_cmd->args && !current_cmd->redirections)
	{
		free_commands(head);
		return (NULL);
	}
	variable_expansion(head, custom_env);
	free_token(head_token);
	return (head);
}

