/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:22:18 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/19 01:10:08 by ael-aiss         ###   ########.fr       */
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

char	**ft_split_plus(char *str, char *sep)
{
	int		count;
	char	**strings;
	int		i;

	if (!str || !sep)
		return (NULL);
	count = count_words(str, sep);
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (str && *str && is_separator(sep, *str))
			str++;
		if (*str)
		{
			strings[i] = word_allocation(str, sep);
			if (!strings[i])
			{
				free_strings(strings);
				return (NULL);
			}
			i++;
		}
		while (str && *str && !is_separator(sep, *str))
			str++;
	}
	strings[i] = NULL;
	return (strings);
}
