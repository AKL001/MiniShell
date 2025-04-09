/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:55:14 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/09 20:42:21 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// char	*handle_word(char *cmd, int *i)
// {
// 	int		len;
// 	char	*str;
// 	char	*tmp;

// 	len = 0;
// 	while (cmd[*i] && !is_operator(cmd[*i]))
// 	{
// 		len++;
// 		(*i)++;
// 	}
// 	str = ft_substr(cmd, *i - len, len);
// 	tmp = trim_whitespace(str);
// 	free(str);
// 	return (tmp);
// }



char	*handle_word(char *cmd, int *i)
{
	int		start;
	char	*str = NULL;
	char	*tmp = NULL;
	char	*quoted;

	start = *i;
	while (cmd[*i] && !is_operator(cmd[*i]) && cmd[*i] != ' ' && cmd[*i] != '\t')
	{
		if (is_quote(cmd[*i]))
		{
			quoted = handle_quote(cmd, i);
			if (!quoted)
				return (NULL);
			if (!str)
				str = quoted;
			else
			{
				tmp = ft_strjoin(str, quoted);
				free(str);
				free(quoted);
				str = tmp;
			}
		}
		else
		{
			int j = *i;
			while (cmd[*i] && !is_operator(cmd[*i]) && !is_quote(cmd[*i]) && cmd[*i] != ' ' && cmd[*i] != '\t')
				(*i)++;
			tmp = ft_substr(cmd, j, *i - j);
			if (!str)
				str = tmp;
			else
			{
				char *joined = ft_strjoin(str, tmp);
				free(str);
				free(tmp);
				str = joined;
			}
		}
	}
	return str;
}