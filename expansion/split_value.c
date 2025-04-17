/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:09:25 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/17 09:30:10 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	count_tokens(char *str)
{
	int	count;
	int	in_quote;

	count = 0;
	in_quote = 0;
	while (*str)
	{
		while (ft_isspace(*str) && !in_quote)
			str++;
		if (!*str)
			break ;
		count++;
		if (*str == '"')
		{
			in_quote = !in_quote;
			str++;
		}
		while ((!ft_isspace(*str) || in_quote) && *str)
		{
			if (*str == '"')
				in_quote = !in_quote;
			str++;
		}
	}
	return (count);
}

static char	*extract_token(char **str)
{
	char	*start;
	char	*token;
	int		len;
	int		in_quote;

	in_quote = 0;
	while (ft_isspace(**str) && !in_quote)
		(*str)++;
	start = *str;
	while ((!ft_isspace(**str) || in_quote) && **str)
	{
		if (**str == '"')
			in_quote = !in_quote;
		(*str)++;
	}
	len = *str - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, start, len);
	token[len] = '\0';
	return (token);
}

char	**split_token_value(char *value)
{
	char	**result;
	int		token_count;
	int		i;

	if (!value)
		return (NULL);
	token_count = count_tokens(value);
	result = malloc(sizeof(char *) * (token_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		result[i] = extract_token(&value);
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[token_count] = NULL;
	return (result);
}
