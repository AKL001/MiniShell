/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:13:49 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/11 09:57:06 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// t_command	*parse_token(t_token *token, t_env *custom_env)
// {
// 	t_command		*current_cmd;
// 	t_command		*head;
// 	t_command		**tail;
// 	t_redir_type	type;
// 	t_token			*head_token;

// 	current_cmd = NULL;
// 	head = NULL;
// 	tail = &head;
// 	head_token = token;

// 	while (token)
// 	{
// 		// helper1
// 		if (!current_cmd)
// 		{
// 			current_cmd = create_command();
// 			if (!current_cmd)
// 			{
// 				free_commands(head);
// 				return (NULL);
// 			}
// 			*tail = current_cmd;
// 			current_cmd->env = custom_env;
// 			tail = &current_cmd->next;
// 		}

// 		if (is_redirection(token->type))
// 		{
// 			type = get_redirection_type(token->type);
// 			token = token->next;
// 			if (!token || token->type != TOKEN_WORD)
// 			{
// 				printf("Syntax error: missing filename after redirection\n");
// 				free_commands(head);
// 				return (NULL);
// 			}
// 			add_command_redirection(current_cmd, type, token->value);
// 			token = token->next;
// 		}

// 		// helper3
// 		else if (token->type == TOKEN_PIPE)
// 		{
// 			if ((!current_cmd->args && !current_cmd->redirections))
// 			{
// 				printf("Syntax error: pipe with no command\n");
// 				free_commands(head);
// 				return (NULL);
// 			}
// 			current_cmd = NULL;
// 			token = token->next;
// 			if (!token)
// 			{
// 				printf("Syntax error: pipe with no command\n");
// 				free_commands(head);
// 				return (NULL);
// 			}
// 		}
// 		// helper 4

// 		else if (token->type == TOKEN_WORD)
// 		{
// 			add_command_args(current_cmd, token->value);
// 			token = token->next;
// 		}
// 		else
// 		{
// 			free_commands(head);
// 			return (NULL);
// 		}
// 	}
// 	// helper 5

// 	if (current_cmd && !current_cmd->args && !current_cmd->redirections)
// 	{
// 		free_commands(head);
// 		return (NULL);
// 	}
// 	variable_expansion(head, custom_env);
// 	free_token(head_token);
// 	return (head);

// // }

t_command	*process_token(t_token **token, t_command *current_cmd,
						t_command *head)
{
	if (is_redirection((*token)->type))
	{
		if (!handle_redirection(token, current_cmd, head))
			return (NULL);
	}
	else if ((*token)->type == TOKEN_PIPE)
	{
		if (!handle_pipe(token, current_cmd, head))
			return (NULL);
		current_cmd = NULL;
	}
	else if ((*token)->type == TOKEN_WORD)
	{
		add_command_args(current_cmd, (*token)->value);
		*token = (*token)->next;
	}
	else
	{
		free_commands(head);
		return (NULL);
	}
	return (current_cmd);
}

t_command	*parse_token(t_token *token, t_env *custom_env)
{
	t_command	*current_cmd;
	t_command	*head;
	t_command	**tail;
	t_token		*head_token;

	current_cmd = NULL;
	head = NULL;
	tail = &head;
	head_token = token;
	while (token)
	{
		if (!current_cmd)
			current_cmd = initialize_command(&head, tail, custom_env);
		current_cmd = process_token(&token, current_cmd, head);
		if (!current_cmd)
			return (NULL);
	}
	if (!validate_final_command(current_cmd, head))
		return (NULL);
	variable_expansion(head, custom_env);
	free_token(head_token);
	return (head);
}
