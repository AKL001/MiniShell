/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 07:22:18 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 10:21:02 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	skip_separators(char **str, char *sep)
{
	while (*str && **str && is_separator(sep, **str))
		(*str)++;
	return (**str != '\0');
}

char	**ft_split_plus(char *str, char *sep)
{
	int		count;
	char	**strings;
	int		i;

	i = 0;
	if (!str || !sep)
		return (NULL);
	count = count_words(str, sep);
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	while (i < count && skip_separators(&str, sep))
	{
		strings[i] = word_allocation(str, sep);
		if (!strings[i])
			return (free_strings(strings), NULL);
		i++;
		while (*str && !is_separator(sep, *str))
			str++;
	}
	strings[i] = NULL;
	return (strings);
}

// char	**ft_split_plus(char *str, char *sep)
// {
// 	int		count;
// 	char	**strings;
// 	int		i;

// 	if (!str || !sep)
// 		return (NULL);
// 	count = count_words(str, sep);
// 	strings = malloc(sizeof(char *) * (count + 1));
// 	if (!strings)
// 		return (NULL);
// 	i = 0;
// 	while (i < count)
// 	{
// 		while (str && *str && is_separator(sep, *str))
// 			str++;
// 		if (*str)
// 		{
// 			strings[i] = word_allocation(str, sep);
// 			if (!strings[i])
// 			{
// 				free_strings(strings);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		while (str && *str && !is_separator(sep, *str))
// 			str++;
// 	}
// 	strings[i] = NULL;
// 	return (strings);
// }
