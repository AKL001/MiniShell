/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:05:16 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/15 18:30:02 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_quoted(char *argument)
{
	int	len;

	if (!argument || !*argument)
		return (0);
	len = ft_strlen(argument);
	if (len >= 2 && is_quote(argument[0]) && argument[len - 1] == argument[0])
		return (1);
	else
		return (0);
}

