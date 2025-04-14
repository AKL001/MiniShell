/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:56:39 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 19:06:02 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*handle_normal_text(char *value, char *s, int *i, char *q)
{
	while (s[*i] && s[*i] != '$')
	{
		if (is_quote(s[*i]))
		{
			get_quote_value(s[*i], q);
		}
		if (!is_quote(s[*i]))
			value = add_char_to_string(s[*i], value);
		else if (s[*i] != *q && *q != 0)
			value = add_char_to_string(s[*i], value);
		(*i)++;
	}
	return (value);
}

char	*expand_string(char *s, t_env *env)
{
	int		i;
	char	q;
	char	*string;

	i = 0;
	q = 0;
	string = NULL;
	if (!env || !s)
		return (NULL);
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			get_quote_value(s[i], &q);
			i++;
		}
		if (s[i] == '$')
			string = handle_dollar(string, s, q, &i, env);
		else
			string = handle_normal_text(string, s, &i, &q);
	}
	return (string);
}
