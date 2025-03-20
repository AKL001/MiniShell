/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:55:14 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:41:13 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*handle_word(char *cmd, int *i)
{
	int		len;
	char	*str;
	char	*tmp;

	len = 0;
	while (cmd[*i] && !is_op_or_quote(cmd[*i]))
	{
		len++;
		(*i)++;
	}
	str = ft_substr(cmd, *i - len, len);
	tmp = trim_whitespace(str);
	free(str);
	return (tmp);
}
