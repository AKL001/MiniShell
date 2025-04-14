/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:55:14 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 19:23:25 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	*add_char_to_string(char c, char *value)
{
	char	*string;
	int		len;
	int		i;

	i = 0;
	if (!value)
		len = 0;
	else
		len = ft_strlen(value);
	if (!c)
		return (value);
	string = malloc(sizeof(char) * (len + 2));
	while (i < len)
	{
		string[i] = value[i];
		i++;
	}
	string[i] = c;
	string[i + 1] = '\0';
	if (value)
		free(value);
	return (string);
}

void	add_new_value_to_tokens(t_token **tokens, char *value)
{
	t_token	*new_token;
	t_token	*last;

	new_token = create_new_token(value);
	if (!new_token)
		return ;
	if (!(*tokens))
		(*tokens) = new_token;
	else
	{
		last = (*tokens);
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

void	add_special_operator(t_token **tokens, int *i, char *cmd)
{
	char	*value;

	if (!cmd)
		return ;
	value = NULL;
	if (is_space(cmd[*i]))
	{
		(*i)++;
		return ;
	}
	value = add_char_to_string(cmd[*i], value);
	(*i)++;
	if (cmd[*i] == cmd[*i - 1])
	{
		value = add_char_to_string(cmd[*i], value);
		(*i)++;
	}
	if (value && *value)
	{
		add_new_value_to_tokens(tokens, value);
		free(value);
	}
}

int	is_split_op(char c)
{
	return (is_space(c) || c == '|' || c == '>' || c == '<');
}
