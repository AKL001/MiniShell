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
#include <stdio.h>

static void	update_env(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current && strcmp(current->key, key))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = strdup(value);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new || !(new->key = strdup(key)) || !(new->value = strdup(value)))
		return ;
	new->next = *env;
	*env = new;
}

static char	*get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (!strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	handle_cd_error(char *msg, int ret)
{
	error_message("No such file or directory\n", 1);
	return (ret);
}

void	my_cd(char **args, t_env **env)
{
	char	cwd[1024];
	char	*target;

	if (!getcwd(cwd, sizeof(cwd)))
		return ((void)handle_cd_error("getcwd", -1));
	target = args[1];
	if (!target && !(target = get_env(*env, "HOME")))
		return ((void)handle_cd_error("cd: HOME not set", 1));
	if (args[2])
		return ((void)handle_cd_error("to many aruments", 1));
	if (chdir(target) == -1)
		return ((void)handle_cd_error("cd: ", 1));
	g_vars.g_exit_status = 0;
	update_env(env, "OLDPWD", cwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return ((void)handle_cd_error("getcwd", 1));
	update_env(env, "PWD", cwd);
}
