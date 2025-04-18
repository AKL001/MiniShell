/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:51:06 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/26 00:51:07 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	update_env(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current && ft_strcmp(current->key, key))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = ft_strdup(value);
		return ;
	}
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return ;
	}
	new->next = *env;
	*env = new;
}

char	*get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	handle_cd_error(char *msg, int ret)
{
	error_message(msg, 1);
	return (ret);
}

static void	save_oldpwd(char *oldpwd, t_env **env)
{
	char	*pwd_from_env;

	if (!getcwd(oldpwd, 1000))
	{
		pwd_from_env = get_env(*env, "PWD");
		if (pwd_from_env)
			ft_strlcpy(oldpwd, pwd_from_env, 1000);
		else
			oldpwd[0] = '\0';
	}
}

void	my_cd(char **args, t_env **env)
{
	char	cwd[1000];
	char	oldpwd[1000];
	char	*target;

	if (!args[1])
	{
		target = get_env(*env, "HOME");
		if (!target)
			return ((void)handle_cd_error("cd: HOME not set\n", 1));
	}
	else
	{
		target = args[1];
		if (args[2])
			return ((void)handle_cd_error("cd: too many arguments\n", 1));
	}
	save_oldpwd(oldpwd, env);
	if (chdir(target) == -1)
		return ((void)handle_cd_error("cd: No such file or directory\n", 1));
	if (oldpwd[0])
		update_env(env, "OLDPWD", oldpwd);
	if (getcwd(cwd, 1000))
		update_env(env, "PWD", cwd);
}

// void	my_cd(char **args, t_env **env)
// {
// 	char	cwd[1000];
// 	char	*target;
// 	char	oldpwd[1000];
// 	// ft_memset(cwd, 0, sizeof(cwd));
// 	if (!args[1])
// 	{
// 		target = get_env(*env, "HOME");
// 		if (!target)
// 			return ((void)handle_cd_error("cd: HOME not set\n", 1));
// 	}
// 	else
// 	{
// 		target = args[1];
// 		if (args[2])
// 			return ((void)handle_cd_error("too many arguments\n", 1));
// 	}
// 	if (!getcwd(oldpwd, sizeof(oldpwd)))
// 		oldpwd = ft_strdup(cwd);
// 	if (chdir(target) == -1)
// 		return ((void)handle_cd_error("cd: \n", 1));
// 	if(oldpwd[0])
// 		update_env(env, "OLDPWD", oldpwd);
// 	if (!getcwd(cwd, sizeof(cwd)))
// 		return ((void)handle_cd_error("getcwd\n", 1));
// 	update_env(env, "PWD", cwd);
// }
