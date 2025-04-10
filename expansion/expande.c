/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:49:30 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 17:16:10 by ael-aiss         ###   ########.fr       */
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

// char *expand_dollar(const char *s, int *i, t_env *env)
// {
// 	int start;
// 	char *key;
// 	char *val;

// 	if (!s)
// 	return (ft_strdup(""));
// 	(*i)++;
// 	start = *i;
// 	if (!s[*i] || s[*i] == '"')
// 		return (ft_strdup("$"));
// 	if (s[*i] == '$')
// 	{
// 		(*i)++;
// 		return (ft_itoa(getpid()));
// 	}
// 	if (s[*i] == '?')
// 	{
// 		(*i)++;
// 		return (ft_itoa(g_vars.g_exit_status));
// 	}
// 	if (s[*i] == '$' || s[*i] == ' ')
// 		return (ft_strdup("$"));
// 	while (s[*i] && ft_isalnum(s[*i]))
// 		(*i)++;
// 	key = ft_substr(s, start, *i - start);
// 	if (!key)
// 		return (NULL);
// 	val = get_env_value_2(key, env);
// 	free(key);
// 	return (val);
// }

// char *expand_string(const char *s, t_env *env)
// {
// 	int		i;
// 	char	*res;
// 	char	*part;

// 	i = 0;
// 	res = NULL;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 			part = handle_single_quote(s, &i);
// 		else if (s[i] == '"')
// 			part = handle_double_quote(s, &i, env);
// 		else if (s[i] == '$')
// 			part = expand_dollar(s, &i, env);
// 		else
// 		{
// 			int start = i;
// 			while (s[i] && s[i] != '$' && !is_quote(s[i]))
// 				i++;
// 			part = ft_substr(s, start, i - start);
// 		}
// 		if (res)
//             res = ft_strjoin_free(res, part);
//         else
//             res = part;
// 	}
// 	return (res);
// }

void	variable_expansion(t_command *command, t_env *custom_env)
{
	t_args	*dollar;
	char	*tmp;

	if (!command)
		return ;
	while (command)
	{
		dollar = command->args;
		while (dollar)
		{
			tmp = dollar->value;
			dollar->value = expand_string(dollar->value, custom_env);
			free(tmp);
			dollar = dollar->next;
		}
		command = command->next;
	}
}
