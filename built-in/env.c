/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:11:54 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:15:05 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	my_env(t_env *custom_env)
{
	t_env	*head;

	if (!custom_env)
		return ;
	head = custom_env;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	g_vars.g_exit_status = 0;
}
