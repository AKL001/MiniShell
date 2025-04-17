/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:00:24 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/17 13:53:25 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	expand_tokens(t_token **tokens, t_env *env)
{
	t_token	*head;
	char	*expand;
	int		is_delim;

	head = *tokens;
	is_delim = 0;
	while (head)
	{
		if (is_delim && head->type == TOKEN_WORD)
			is_delim = 0;
		else
		{
			if (head->type == TOKEN_HEREDOC)
				is_delim = 1;
			else
			{
				expand = expand_string(head->value, env);
				free(head->value);
				head->value = expand;
			}
		}
		head = head->next;
	}
}

int	check_value(char **value)
{
	int	i;

	i = 0;
	if (!value || !*value)
		return (0);
	while (value[i])
	{
		i++;
	}
	if (i > 1)
	{
		return (1);
	}
	return (0);
}

void	insert_new_token(t_token *current, char **value)
{
	int		i;
	t_token	*next;
	t_token	*new;
	t_token	*tmp;

	i = 1;
	next = current->next;
	free(current->value);
	current->value = ft_strdup(value[0]);
	tmp = current;
	while (value[i])
	{
		new = create_new_token(value[i]);
		new->next = tmp->next;
		tmp->next = new;
		tmp = new;
		i++;
	}
	tmp->next = next;
}

void	field_split(t_token **tokens)
{
	t_token	*current;
	char	**value;

	current = *tokens;
	while (current)
	{
		value = split_token_value(current->value);
		if (check_value(value))
		{
			insert_new_token(current, value);
		}
		free_array(value);
		current = current->next;
	}
}
