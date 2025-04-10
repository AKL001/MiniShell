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

void	my_pwd(char **args)
{
	char	path[1024];

	(void)args;
	if (getcwd(path, sizeof(path)) == NULL)
	{
		error_message("pwd: ", 1);
		return ;
	}
	printf("%s\n", path);
	g_vars.g_exit_status = 0;
}
