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
