/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:24:45 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:47:38 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_op_or_quote(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"');
}

int	is_operator(char c)
{
	if (!c)
		return (0);
	return (c == '|' || c == '<' || c == '>');
}

int	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	inside_quotes(char *str)
{
	int		len;

	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
	{
		return (1);
	}
	return (0);
}
