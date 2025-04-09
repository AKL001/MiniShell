// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expande.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/20 23:49:30 by ael-aiss          #+#    #+#             */
// /*   Updated: 2025/04/09 20:48:10 by ael-aiss         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/header.h"

// int is_quote(char c)
// {
// 	return (c == '"' || c == '\'');
// }



char *ft_strjoin_free(char *s1, char *s2)
{
	char *out;
	if (!s2)
		return (ft_strdup(""));
	out = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (out);
}

static char *get_env_value_2(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char *expand_dollar(const char *s, int *i, t_env *env)
{
	int start;
	char *key;
	char *val;

	(*i)++;
	start = *i;
	while (s[*i] && (s[*i] == '_' || ft_isalnum(s[*i])))
		(*i)++;
	key = ft_substr(s, start, *i - start);
	val = get_env_value_2(key, env);
	free(key);
	return (val);
}

char *handle_single_quote(const char *s, int *i)
{
	int start;
	char *out;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	out = ft_substr(s, start, *i - start);
	if (s[*i] == '\'')
		(*i)++;
	return (out);
}

char *handle_double_quote(const char *s, int *i, t_env *env)
{
	char *res;
	char *part;

	res = NULL;
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			part = expand_dollar(s, i, env);
		else
		{
			int start = *i;
			while (s[*i] && s[*i] != '$' && s[*i] != '"')
				(*i)++;
			part = ft_substr(s, start, *i - start);
		}
		if (res)
			res = ft_strjoin_free(res, part);
		else
			res = part;
	}
	if (s[*i] == '"')
		(*i)++;
	if (!res)
		return (ft_strdup(""));
	return (res);
}


char *expand_string(const char *s, t_env *env)
{
	int i;
	char *res;
	char *part;

	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == '\'')
			part = handle_single_quote(s, &i);
		else if (s[i] == '"')
			part = handle_double_quote(s, &i, env);
		else if (s[i] == '$')
			part = expand_dollar(s, &i, env);
		else
		{
			int start = i;
			while (s[i] && s[i] != '$' && !is_quote(s[i]))
				i++;
			part = ft_substr(s, start, i - start);
		}
		res = res ? ft_strjoin_free(res, part) : part;
	}
	return (res);
}

void variable_expansion(t_command *command, t_env *custom_env)
{
	char *key;
	t_args *dollar;

	if (!command)
		return;
	while (command)
	{
		dollar = command->args;
		while (dollar)
		{
			char *tmp = dollar->value;
			dollar->value = expand_string(dollar->value, custom_env);
			free(tmp);
			dollar = dollar->next;
		}
		// strip_backslash(&command->args);
		command = command->next;
	}
}