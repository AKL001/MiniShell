/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:31:48 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/18 10:33:57 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	update_env_var(t_env *head, char *key, char *value)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			free(head->value);
			head->value = ft_strdup(value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static void	append_env_node(t_env **custom_envp, t_env *new_node)
{
	t_env	*head;

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

void	add_envp_var(t_env **custom_envp, char *key, char *value, int overwrite)
{
	t_env	*new_node;
	t_env	*head;

	if (!custom_envp || !key || !value)
		return ;
	if (overwrite && *custom_envp && update_env_var(*custom_envp, key, value))
		return ;
	if (!overwrite)
	{
		head = *custom_envp;
		while (head)
		{
			if (ft_strcmp(head->key, key) == 0)
				return ;
			head = head->next;
		}
	}
	new_node = create_new(key, value);
	if (!new_node)
		return ;
	if (new_node)
		append_env_node(custom_envp, new_node);
}

static int	process_export_arg(t_env **env, char *arg)
{
	char	*plus_equal;
	char	*equal;
	char	*key;

	plus_equal = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus_equal)
		return (handle_plus_equal_case(env, arg, plus_equal));
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_strndup(arg, equal - arg);
		if (is_valid_identifier(key) == 1)
			return (add_envp_var(env, key, equal + 1, 1), free(key), 1);
		free(key);
	}
	else
	{
		if (is_valid_identifier(arg) == 1)
			return (add_envp_var(env, arg, "", 0), 1);
	}
	write(2, "export: not a valid identifier\n", 31);
	return (0);
}

void	my_export(t_env **env, char **args)
{
	if (!args[1])
		return (print_export(*env), (void)(g_vars.g_exit_status = 0));
	while (*++args)
	{
		if (!process_export_arg(env, *args))
		{
			g_vars.g_exit_status = 1;
			return ;
		}
	}
	g_vars.g_exit_status = 0;
}
// static int	process_export_arg(t_env **env, char *arg)
// {
// 	char	*equal;
// 	char	*key;
// 	int		valid;
// 	char *plus_equal;
// 	char	*existing;
// 	char	*new_value;

// 	plus_equal = ft_strnstr(arg, "+=", ft_strlen(arg));
// 	if (plus_equal)
// 	{
// 		valid = is_valid_identifier(arg);
// 		if (valid)
// 		{
// 			key = ft_strndup(arg, plus_equal - arg);
// 			existing = get_env(*env, key);
// 			if (existing)
// 				new_value = ft_strjoin(existing, plus_equal + 2);
// 			else
// 				new_value = ft_strjoin("", plus_equal + 2);
// 			add_envp_var(env, key, new_value, 1);
// 			free(key);
// 			free(new_value);
// 		}
// 		else
// 			write(2, "export: not a valid identifier\n", 31);
// 		return (valid);
// 	}
// 	equal = ft_strchr(arg, '=');
// 	if (equal)
// 	{
// 		key = ft_strndup(arg, equal - arg);
// 		valid = is_valid_identifier(key);
// 		if (valid)
// 			add_envp_var(env, key, equal + 1, 1);
// 		else
// 			write(2, "export: not a valid identifier\n", 31);
// 		free(key);
// 	}
// 	else
// 	{
// 		valid = is_valid_identifier(arg);
// 		if (valid)
// 			add_envp_var(env, arg, "", 0);
// 		else
// 			write(2, "export: not a valid identifier\n", 31);
// 	}
// 	return (valid);
// }
// void	my_export(t_env **env, char **args)
// {
// 	int		i;
// 	char	*equal;
// 	char	*key;
// 	char	*value;

// 	if (!args[1])
// 		return (print_export(*env),(void)(g_vars.g_exit_status = 0));
// 	while (args[i])
// 	{
// 		equal = ft_strchr(args[i], '=');
// 		if (equal)
// 		{
// 			*equal = '\0';
// 			key = args[i];
// 			value = equal + 1;
// 			if (is_valid_identifier(key))
// 				add_envp_var(env, key, value,1);
// 			else
// 			{
// 				write(2, "export: not a valid identifier\n", 31);
// 				g_vars.g_exit_status = 1;
// 				return ;
// 			}
// 			*equal = '=';
// 		}
// 		else if (is_valid_identifier(args[i]))
// 			add_envp_var(env, args[i], "",0);
// 		else
// 		{
// 			write(2, "export: not a valid identifier\n", 31);
// 			g_vars.g_exit_status = 1;
// 			return ;
// 		}
// 		i++;
// 	}
// 	g_vars.g_exit_status = 0;
// }
