/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:33:17 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 22:33:20 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !(str[0] == '_' || (str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z')))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		if (str[i] == '+')
			return (0);
		if (!(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0'
					&& str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_path(const char *path)
{
	struct stat	info;

	if (!path)
		return (0);
	return (stat(path, &info) == 0);
}

char	*get_env_export(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

int	handle_plus_equal_case(t_env **env, char *arg, char *plus_equal)
{
	char	*key;
	char	*existing;
	char	*new_value;
	int		valid;

	valid = is_valid_identifier(arg);
	if (!valid)
	{
		write(2, "export: not a valid identifier\n", 31);
		return (valid);
	}
	key = ft_strndup(arg, plus_equal - arg);
	existing = get_env_export(*env, key);
	if (existing)
		new_value = ft_strjoin(existing, plus_equal + 2);
	else
		new_value = ft_strdup(plus_equal + 2);
	add_envp_var(env, key, new_value, 1);
	free(key);
	free(new_value);
	return (valid);
}
