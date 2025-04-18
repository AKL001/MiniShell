/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:20 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:15:21 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	my_exit(char **args, t_env *env)
{
	int	exit_code;

	printf("exit\n");
	if (args[1] && args[2])
	{
		error_message("exit: too many arguments\n", 1);
		g_vars.g_exit_status = 1;
		return ;
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			error_message("exit: numeric argument required\n", 2);
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		free_env(env);
		exit(exit_code);
	}
	free_env(env);
	exit(g_vars.g_exit_status);
}
