/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:46 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:15:50 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	my_pwd(t_env *env)
{
	char	path[1024];
	t_env	*curr_pwd;

	if (getcwd(path, sizeof(path)) == NULL)
	{
		curr_pwd = env;
		while (curr_pwd)
		{
			if (ft_strcmp(curr_pwd->key, "PWD") == 0 && curr_pwd->value)
			{
				printf("%s\n", curr_pwd->value);
				g_vars.g_exit_status = 0;
				return ;
			}
			curr_pwd = curr_pwd->next;
		}
		g_vars.g_exit_status = 1;
		return ;
	}
	printf("%s\n", path);
	g_vars.g_exit_status = 0;
}
