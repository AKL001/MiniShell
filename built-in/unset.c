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


// void	remove_env_var(t_env **env, t_env *cur, t_env *prev, char *arg)
// {
// 	t_env	*tmp;

// 	if (ft_strcmp(arg, cur->key) == 0)
// 	{
// 		tmp = cur;
// 		if (!prev)
// 			*env = cur->next;
// 		else
// 			prev->next = cur->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 	}
// }
void remove_env_var(t_env **env, t_env *cur, t_env *prev)
{
    t_env *tmp = cur;

    if (!prev)
    {
		*env = cur->next;
	}
    else
        prev->next = cur->next;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
}

// node: 1 2 3 4 

void my_unset(t_env **env, char **args)
{
    t_env *cur;
    t_env *prev;
    int i;

    if (!args)
        return;
    i = 1;
    while (args[i])
    {
        cur = *env;
        prev = NULL;
        while (cur)
        {
            if (ft_strcmp(args[i], cur->key) == 0 && cur->key[0] != '_')
            {
                if (!prev)
                    *env = cur->next;
                else
                    prev->next = cur->next;
                free(cur->key);
                free(cur->value);
                free(cur);
                break; // important: stop after deleting
            }
            prev = cur;
            cur = cur->next;
        }
        i++;
    }
    g_vars.g_exit_status = 0;
}


// void my_unset(t_env **env, char **args)
// {
//     t_env *cur;
//     t_env *prev;

// 	t_env *next;
//     int i;

//     if (!args || !env || !*env)
//         return;
//     i = 1;
//     while (args[i])
//     {
//         cur = *env;
//         prev = NULL;
//         while (cur)
//         {
//             next = cur->next;
// 			// key = PATH next -> HOME
//             if (ft_strcmp(args[i], cur->key) == 0)
//                 remove_env_var(env, cur, prev);
// 			else 
// 				prev = cur;
// 			cur = next;
//         }
//         i++;
//     }
//     g_vars.g_exit_status = 0;
// }

// void	my_unset(t_env **env, char **args)
// {
// 	t_env	*cur;
// 	t_env	*prev;
// 	int		i;

// 	if (!args)
// 		return ;
// 	i = 1;
// 	while (args[i])
// 	{
// 		cur = *env;
// 		prev = NULL;
// 		while (cur)
// 		{
// 			remove_env_var(env, cur, prev, args[i]);
// 			prev = cur;
// 			cur = cur->next;
// 		}
// 		i++;
// 	}
// 	g_vars.g_exit_status = 0;
// }

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