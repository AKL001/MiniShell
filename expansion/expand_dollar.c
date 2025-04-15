/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:16:31 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/15 17:43:44 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*get_env_value_2(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

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

char	*add_var_value(char *string, char *s, t_env *env, int *i)
{
	char	*key;
	char	*value;
	int		j;

	j = 0;
	key = NULL;
	if (s[*i] == '$')
		(*i)++;
	while (ft_isalnum(s[*i]))
	{
		key = add_char_to_string(s[*i], key);
		(*i)++;
	}
	value = get_env_value_2(key, env);
	free(key);
	if (value)
	{
		while (value[j])
		{
			string = add_char_to_string(value[j], string);
			j++;
		}
		free(value);
	}
	return (string);
}
