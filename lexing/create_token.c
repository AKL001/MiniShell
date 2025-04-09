/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:18:57 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/09 20:41:02 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_token_type	set_type_token(char *value)
{
	t_token_type	type;

	if (ft_strncmp(value, "|", 2) == 0)
		type = TOKEN_PIPE;
	else if (ft_strncmp(value, "<", 2) == 0)
		type = TOKEN_REDIRECT_IN;
	else if (ft_strncmp(value, ">", 2) == 0)
		type = TOKEN_REDIRECT_OUT;
	else if (ft_strncmp(value, ">>", 3) == 0)
		type = TOKEN_APPEND;
	else if (ft_strncmp(value, "<<", 3) == 0)
		type = TOKEN_HEREDOC;
	else
		type = TOKEN_WORD;
	return (type);
}

t_token	*create_new_token(char *value)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		return (NULL);
	new_token->next = NULL;
	new_token->type = set_type_token(value);
	return (new_token);
}

void	add_new_token(t_token **tokens, char *val)
{
	t_token	*new_token;
	t_token	*head;
	int		i;
	char	**value;

	i = 0;
	if (!inside_quotes(val))
	{
		value = ft_split_plus(val, " \t");
		while (value[i])
		{
			new_token = create_new_token(value[i]);
			if (!new_token)
				return ;
			if (!*tokens)
				*tokens = new_token;
			else
			{
				head = *tokens;
				while (head->next)
					head = head->next;
				head->next = new_token;
			}
			i++;
		}
		free_strings(value);
	}
	else
	{
		new_token = create_new_token(val);
		if (!new_token)
			return ;
		if (!*tokens)
			*tokens = new_token;
		else
		{
			head = *tokens;
			while (head->next)
				head = head->next;
			head->next = new_token;
		}
	}
}
