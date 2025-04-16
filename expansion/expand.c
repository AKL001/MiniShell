/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:00:24 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/16 21:09:17 by ael-aiss         ###   ########.fr       */
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


void update_quote_status(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '\"'))
		*q = c;
	else if (*q == c)
		*q = 0;
}

char **add_split_piece(char **arr, char *start, int len)
{
	char **new_arr;
	int i;
	int count;

	count = 0;
	while (arr && arr[count])
		count++;
	new_arr = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_substr(start, 0, len);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

char **split_token_value(char *value)
{
	int i;
	int start;
	char q;
	char **res;

	i = 0;
	start = 0;
	q = 0;
	res = NULL;
	while (value[i])
	{
		update_quote_status(value[i], &q);
		if ((value[i] == ' ' || value[i] == '\t') && q == 0)
		{
			if (i > start)
				res = add_split_piece(res, value + start, i - start);
			while (value[i] == ' ' || value[i] == '\t')
				i++;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		res = add_split_piece(res, value + start, i - start);
	return (res);
}

int check_value(char **value)
{
	int i;

	i = 0;
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

void insert_new_token(t_token *current, char **value)
{
	int i;
	t_token *next;
	t_token *new;
	t_token *tmp;

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

void field_split(t_token **tokens)
{
	t_token *current;
	char **value;

	current = *tokens;
	while (current)
	{
		value = split_token_value(current->value);
		if (check_value(value))
		{
			insert_new_token(current, value);
			free_array(value);
		}
		current = current->next;
	}
}
