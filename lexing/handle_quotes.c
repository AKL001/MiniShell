/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:54:44 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 10:50:19 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*handle_quote(char *cmd, int *i)
{
	char	quote;
	int		len;
	char	*str;

	quote = cmd[*i];
	len = 0;
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
	{
		len++;
		(*i)++;
	}
	str = ft_substr(cmd, *i - len - 1, len + 2);
	if (!str)
		return (NULL);
	(*i)++;
	return (str);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
