/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:21:03 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:53:40 by ael-aiss         ###   ########.fr       */
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

int	get_index_char(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	cnout_char_in_substr(char *str, int start, int end, char c)
{
	int	count;

	count = 0;
	while (start < end)
	{
		if (str[start] == c)
			count++;
		start++;
	}
	return (count);
}

int	check_quote_inside(char *cmd)
{
	char	quote;
	int		i;
	int		d;
	int		s;

	i = 0;
	d = 0;
	s = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_quote(cmd[i]) == 0)
			i++;
		if (is_quote(cmd[i]) == 1)
		{
			quote = cmd[i];
			if (quote == '"')
				d = 1;
			else
				s = 1;
			i++;
		}
		while (cmd[i] && cmd[i] != quote)
			i++;
		if (is_quote(cmd[i]) == 1)
		{
			quote = cmd[i];
			if (quote == '"')
				d = 0;
			else
				s = 0;
			i++;
		}
	}
	return (d == 0 && s == 0);
}

int	check_unclosed_quotes(char *cmd)
{
	int	single_quotes;
	int	double_quotes;

	if (!cmd)
		return (0);
	double_quotes = count_char(cmd, '"');
	single_quotes = count_char(cmd, '\'');
	if (double_quotes == 0 && single_quotes == 0)
		return (1);
	else if (single_quotes % 2 != 0 && double_quotes == 0)
		return (0);
	else if (double_quotes % 2 != 0 && single_quotes == 0)
		return (0);
	else if (single_quotes % 2 == 0 && double_quotes == 0)
		return (1);
	else if (double_quotes % 2 == 0 && single_quotes == 0)
		return (1);
	else
		return (check_quote_inside(cmd));
}
