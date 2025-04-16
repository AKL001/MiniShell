/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:14:13 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:14:14 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_valid_n_flag(char *s)
{
	int	i;

	i = 0;
	if (!s || s[i++] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_write_error(void)
{
	perror("write :");
	return (1);
}

int	my_echo(t_env *custom_envp, char **args)
{
	int	i;
	int	new_line;
	int	result;

	(void)custom_envp;
	i = 1;
	new_line = 1;
	result = 0;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		if (ft_putstr_fd(args[i], 1) == -1)
			result = handle_write_error();
		if (args[i + 1] && ft_putchar_fd(' ', 1) == -1)
			result = 1;
		i++;
	}
	if (new_line && ft_putchar_fd('\n', 1) == -1)
		result = 1;
	g_vars.g_exit_status = result;
	return (result);
}

// int	my_echo(t_env *custom_envp, char **args)
// {
// 	int	i;
// 	int	new_line;

// 	(void)custom_envp;
// 	i = 1;
// 	new_line = 1;
// 	while (args[i] && is_valid_n_flag(args[i]))
// 	{
// 		new_line = 0;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i], 1);
// 		if (args[i + 1])
// 			ft_putchar_fd(' ', 1);
// 		i++;
// 	}
// 	if (new_line)
// 		ft_putchar_fd('\n', 1);
// 	g_vars.g_exit_status = 0;
// 	return (0);
// }
