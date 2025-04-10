/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:42 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:22:30 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_env	*create_new(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	update_existing_var(t_env *head, char *key, char *value)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			free(head->value);
			head->value = ft_strdup(value);
			return ;
		}
		head = head->next;
	}
}

void	add_new_var(t_env **custom_envp, char *key, char *value)
{
	t_env	*new_node;
	t_env	*head;

	new_node = create_new(key, value);
	if (!new_node)
		return ;
	if (!*custom_envp)
	{
		*custom_envp = new_node;
		return ;
	}
	head = *custom_envp;
	while (head->next)
		head = head->next;
	head->next = new_node;
}

void	add_env_var(t_env **custom_envp, char *key, char *value)
{
	if (!custom_envp || !key || !value)
		return ;
	update_existing_var(*custom_envp, key, value);
	add_new_var(custom_envp, key, value);
}

t_env	*init_envp(char **envp)
{
	int		i;
	char	*equal;
	char	*key;
	char	*entry;
	t_env	*custom_envp;

	custom_envp = NULL;
	i = 0;
	while (envp[i])
	{
		entry = ft_strdup(envp[i]);
		if (!entry)
			return (NULL);
		equal = ft_strchr(entry, '=');
		if (equal)
		{
			*equal = '\0';
			key = entry;
			add_env_var(&custom_envp, key, equal + 1);
		}
		free(entry);
		i++;
	}
	return (custom_envp);
}

// void add_env_var(t_env **custom_envp, char *key, char *value)
// {
//     t_env *new_node, *head;

//     if (!custom_envp || !key || !value)
//         return ;
//     head = *custom_envp;
//     while (head)
//     {
//         if (ft_strcmp(head->key, key) == 0)
//         {
//             free(head->value);
//             head->value = ft_strdup(value);
//             return ;
//         }
//         head = head->next;
//     }
//     new_node = create_new(key, value);
//     if (!new_node)
//         return ;
//     if (!*custom_envp)
//     {
//         *custom_envp = new_node;
//         return ;
//     }
//     head = *custom_envp;
//     while (head->next)
//         head = head->next;
//     head->next = new_node;
// }