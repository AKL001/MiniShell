/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:55:14 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 10:41:37 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

static char	*handle_plain_text(char *cmd, int *i, char *str)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	while (cmd[*i] && !is_operator(cmd[*i]) && !is_quote(cmd[*i])
		&& cmd[*i] != ' ' && cmd[*i] != '\t')
		(*i)++;
	tmp = ft_substr(cmd, j, *i - j);
	if (!str)
		return (tmp);
	return (join_and_free(str, tmp));
}

char	*handle_word(char *cmd, int *i)
{
	char	*str;
	char	*quoted;

	str = NULL;
	quoted = NULL;
	while (cmd[*i] && !is_operator(cmd[*i]) && cmd[*i] != ' '
		&& cmd[*i] != '\t')
	{
		if (is_quote(cmd[*i]))
		{
			quoted = handle_quote(cmd, i);
			if (!quoted)
				return (NULL);
			if (!str)
				str = quoted;
			else
				str = join_and_free(str, quoted);
		}
		else
			str = handle_plain_text(cmd, i, str);
	}
	return (str);
}

// char	*handle_word(char *cmd, int *i)
// {
// 	int start;
// 	char *str = NULL;
// 	char *tmp = NULL;
// 	char *quoted;

// 	start = *i;
// 	while (cmd[*i] && !is_operator(cmd[*i]) && cmd[*i] != ' '
// 		&& cmd[*i] != '\t')
// 	{
// 		if (is_quote(cmd[*i]))
// 		{
// 			quoted = handle_quote(cmd, i);
// 			if (!quoted)
// 				return (NULL);
// 			if (!str)
// 				str = quoted;
// 			else
// 			{
// 				tmp = ft_strjoin(str, quoted);
// 				free(str);
// 				free(quoted);
// 				str = tmp;
// 			}
// 		}
// 		else
// 		{
// 			int j = *i;
// 			while (cmd[*i] && !is_operator(cmd[*i]) && !is_quote(cmd[*i])
// 				&& cmd[*i] != ' ' && cmd[*i] != '\t')
// 				(*i)++;
// 			tmp = ft_substr(cmd, j, *i - j);
// 			if (!str)
// 				str = tmp;
// 			else
// 			{
// 				char *joined = ft_strjoin(str, tmp);
// 				free(str);
// 				free(tmp);
// 				str = joined;
// 			}
// 		}
// 	}
// 	return (str);
// }
