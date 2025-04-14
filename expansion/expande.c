/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:49:30 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 15:10:18 by ael-aiss         ###   ########.fr       */
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
