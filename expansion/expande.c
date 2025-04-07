/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:49:30 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/07 10:37:58 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int check_lenght(char *str1, char *str2)
{
	return (ft_strlen(str1) == ft_strlen(str2));	
}

char *retrieve_variable_value(t_env *custom_env, char *key)
{
	char *value;
	int len;

	value = NULL;
	if (!key || !custom_env)
		return (NULL);
	while (custom_env)
	{
		len = ft_strlen(custom_env->key);
		if (ft_strncmp(custom_env->key, key, len) == 0 && check_lenght(custom_env->key,key))
		{
			value = ft_strdup(custom_env->value);
			break;
		}
		custom_env = custom_env->next;
	}
	return (value);
}

int back_slash_exist(char *str, int *index)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void strip_backslash(t_args **args)
{
	int i;
	t_args *arg;
	char *after_slach;
	char *new_value;
	char *value;

	arg = *args;
	while (arg)
	{
		while (back_slash_exist(arg->value, &i))
		{
			value = arg->value;
			value[i] = '\0';
			after_slach = value + i + 1;
			new_value = ft_strjoin(value, after_slach);
			arg->value = new_value;
			free(value);
		}
		arg = arg->next;
	}
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
