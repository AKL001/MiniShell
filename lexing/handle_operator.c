/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 07:26:19 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/18 06:47:56 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*handle_operator(char *cmd, int *i)
{
	int		len;
	char	*str;

	len = 1;
	if (is_operator(cmd[*i + 1]))
		len = 2;
	str = ft_substr(cmd, *i, len);
	if (!str)
		return (NULL);
	(*i) += len;
	return (str);
}
