/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:22:04 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/19 06:57:21 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*trim_whitespace(char *input)
{
	int		start;
	int		end;
	char	*str;

	if (!input || !*input)
		return (NULL);
	start = 0;
	while (input[start] == '\t' || input[start] == ' ')
		start++;
	end = ft_strlen(input) - 1;
	while (input[end] == ' ' || input[end] == '\t')
		end--;
	if (start > end)
		str = ft_strdup("");
	else
		str = ft_substr(input, start, end - start + 1);
	return (str);
}
