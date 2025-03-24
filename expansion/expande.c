/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:49:30 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/23 00:15:53 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char *retrieve_variable_value(t_env *custom_env, char *key)
{
	char *value;
	int len;

	value = NULL;
	if (!key || !custom_env)
		return (NULL);
	while (custom_env)
	{
		len = ft_strlen(key);
		if (ft_strncmp(custom_env->key, key, len) == 0)
		{
			value = ft_strdup(custom_env->value);
			break;
		}
		custom_env = custom_env->next;
	}
	if (value)
		return (value);
	else
		return (NULL);
}

void strip_backslash(t_args **args)
{
	int i;
	t_args *arg;
	
	arg = *args;
	char *after_slach;
	char *new_value;
	char *value;
	while (arg)
	{
		value = arg->value;
		i = 0;
		while (value[i])
		{
			if (value[i] == '\\' && value[i + 1] == '$')
			{
				value[i] = '\0';
				after_slach = value + i + 1;
				new_value = ft_strjoin(value, after_slach);
				(*args)->value = new_value;
				free(value);
			}
			i++;
		}
		arg = arg->next;
	}
}

void variable_expansion(t_command *command, t_env *custom_env)
{
	char *key;
	t_args *dollar;

	if (!command)
		return ;
	while (command)
	{
		dollar = command->args;
		while (dollar)
		{
			key = dollar_verification(dollar->value);
			if (!key || !*key) // attention about key is empty but not null !!
				dollar = dollar->next;
			else
				assign_variable_value(&(dollar->value), key, custom_env);
		}
		strip_backslash(&command->args);
		command = command->next;
	}
}
