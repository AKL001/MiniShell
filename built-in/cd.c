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

void	my_cd(char **args)
{
	DIR		*dir;
	int		count;
	char	*path;

	while (args[count])
		count++;
	if (count > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (count == 1)
		path = getenv("HOME");
	else
		path = args[1];
	dir = opendir(path);
	if (!dir)
	{
		perror(path);
		return ;
	}
	chdir(path);
	closedir(dir);
}
