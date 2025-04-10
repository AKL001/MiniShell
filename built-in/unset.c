/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:55 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:19:56 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	remove_env_var(t_env **env, t_env *cur, t_env *prev, char *arg)
{
	t_env	*tmp;

	if (ft_strcmp(arg, cur->key) == 0)
	{
		tmp = cur;
		if (!prev)
			*env = cur->next;
		else
			prev->next = cur->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	my_unset(t_env **env, char **args)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	i = 1;
	while (args[i])
	{
		cur = *env;
		prev = NULL;
		while (cur)
		{
			remove_env_var(env, cur, prev, args[i]);
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	g_vars.g_exit_status = 0;
}

// void	my_unset(t_env **env, char **args)
// {
// 	t_env	*cur;
// 	t_env	*prev;
// 	t_env	*tmp;
// 	int		i;

// 	i = 1;
// 	while (args[i])
// 	{
// 		cur = *env;
// 		prev = NULL;
// 		while (cur)
// 		{
// 			if (ft_strcmp(args[i], cur->key) == 0)
// 			{
// 				tmp = cur;
// 				if (!prev)
// 					*env = cur->next;
// 				else
// 					prev->next = cur->next;
// 				free(tmp->key);
// 				free(tmp->value);
// 				free(tmp);
// 				break ;
// 			}
// 			prev = cur;
// 			cur = cur->next;
// 		}
// 		i++;
// 	}
// 	g_vars.g_exit_status = 0;
// }