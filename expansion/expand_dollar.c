/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:16:31 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 19:26:37 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*get_key_value(char *s, int *i)
{
	char	*key;

	key = NULL;
	if (!s)
		return (NULL);
	if (s[*i] == '$')
		(*i)++;
	while (s[*i] && !is_op_or_quote(s[*i]) && !is_space_or_tab(s[*i]))
	{
		key = add_char_to_string(s[*i], key);
		(*i)++;
	}
	return (key);
}

char	*handle_exit_case(char *value)
{
	char	*exit_status;
	int		i;

	exit_status = ft_itoa(g_vars.g_exit_status);
	i = 0;
	while (exit_status[i])
	{
		value = add_char_to_string(exit_status[i], value);
		i++;
	}
	free(exit_status);
	return (value);
}

char	*expand_dollar(char *value, char *s, int *i, t_env *env)
{
	char	*key;
	int		j;
	char	*var_value;

	j = 0;
	key = get_key_value(s, i);
	if (!key)
		return (value);
	var_value = get_env_value_2(key, env);
	if (var_value && *var_value)
	{
		while (var_value[j])
		{
			value = add_char_to_string(var_value[j], value);
			j++;
		}
	}
	free(var_value);
	free(key);
	return (value);
}

char	*handle_dollar(char *value, char *s, char q, int *i, t_env *env)
{
	if (q == '\'')
	{
		value = add_char_to_string(s[*i], value);
		(*i)++;
	}
	else if (s[*i + 1] && s[*i + 1] == '?')
	{
		value = handle_exit_case(value);
		(*i) += 2;
	}
	else if (!ft_isalnum(s[*i + 1]))
	{
		value = add_char_to_string(s[*i], value);
		(*i)++;
	}
	else
		value = expand_dollar(value, s, i, env);
	return (value);
}
