/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:20:22 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 10:21:35 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_separator(char *sep, char c)
{
	int	i;

	i = 0;
	if (!sep)
		return (0);
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *input, char *separator)
{
	int	count;
	int	i;

	count = 0;
	if (!input || !separator)
		return (0);
	i = 0;
	while (input[i])
	{
		while (input[i] && is_separator(separator, input[i]))
			i++;
		if (input[i])
		{
			count++;
			i++;
		}
		while (input[i] && !is_separator(separator, input[i]))
			i++;
	}
	return (count);
}

int	len_word(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !is_separator(sep, str[i]))
		i++;
	return (i);
}

char	*word_allocation(char *str, char *sep)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (str[len] && !is_separator(sep, str[len]))
	{
		len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
