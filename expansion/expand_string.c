/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:56:39 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 15:48:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*handle_normal_text(const char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != '$' && !is_quote(s[*i]))
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

static char	*get_next_part(const char *s, int *i, t_env *env)
{
	if (s[*i] == '\'')
		return (handle_single_quote(s, i));
	if (s[*i] == '"')
		return (handle_double_quote(s, i, env));
	if (s[*i] == '$')
		return (expand_dollar(s, i, env));
	return (handle_normal_text(s, i));
}

static char	*join_parts(char *res, char *part)
{
	if (!res)
		return (part);
	return (ft_strjoin_free(res, part));
}

char	*expand_string(const char *s, t_env *env)
{
	int		i;
	char	*res;
	char	*part;

	i = 0;
	res = NULL;
	while (s[i])
	{
		part = get_next_part(s, &i, env);
		res = join_parts(res, part);
	}
	if (res)
		return (res);
	else
		return (ft_strdup(""));
}
