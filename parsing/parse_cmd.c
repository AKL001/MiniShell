/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:13:49 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:34 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	prepare_command_if_needed(t_command **current_cmd, t_command **head,
		t_command ***tail, t_env *env)
{
	if (*current_cmd)
		return (1);
	*current_cmd = create_command();
	if (!(*current_cmd))
	{
		free_commands(*head);
		return (0);
	}
	**tail = *current_cmd;
	(*current_cmd)->env = env;
	*tail = &((*current_cmd)->next);
	return (1);
}

int	handle_redirection(t_token **token, t_command *cmd, t_command *head)
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
	add_command_redirection(cmd, type, (*token)->value);
	*token = (*token)->next;
	return (1);
}

int	handle_pipe_token(t_token **token, t_command **current_cmd, t_command *head)
{
	if (!(*current_cmd)->args && !(*current_cmd)->redirections)
	{
		printf("Syntax error: pipe with no command\n");
		free_commands(head);
		return (0);
	}
	*current_cmd = NULL;
	*token = (*token)->next;
	if (!(*token))
	{
		printf("Syntax error: pipe with no command\n");
		free_commands(head);
		return (0);
	}
	return (1);
}

int	process_token_type(t_token **token, t_command **current_cmd,
		t_command *head)
{
	if (is_redirection((*token)->type))
	{
		if (!handle_redirection(token, *current_cmd, head))
			return (0);
	}
	else if ((*token)->type == TOKEN_PIPE)
	{
		if (!handle_pipe_token(token, current_cmd, head))
			return (0);
	}
	else if ((*token)->type == TOKEN_WORD)
	{
		add_command_args(*current_cmd, (*token)->value);
		*token = (*token)->next;
	}
	else
	{
		free_commands(head);
		return (0);
	}
	return (1);
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
		if (!prepare_command_if_needed(&current_cmd, &head, &tail, custom_env))
			return (NULL);
		if (!process_token_type(&token, &current_cmd, head))
			return (NULL);
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
