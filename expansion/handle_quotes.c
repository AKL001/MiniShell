/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:47:50 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:10 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// char *ft_strjoin_free(char *s1, char *s2)
// {
// 	char *out;

// 	if (!s2)
// 		return (s1 ? s1 : ft_strdup(""));
// 	out = ft_strjoin(s1, s2);
// 	free(s1);
// 	free(s2);
// 	return (out);
// }

// char *handle_single_quote(const char *s, int *i)
// {
// 	int		start;
// 	char	*out;

// 	(*i)++;
// 	start = *i;
// 	while (s[*i] && s[*i] != '\'')
// 		(*i)++;
// 	out = ft_substr(s, start, *i - start);
// 	if (s[*i] == '\'')
// 		(*i)++;
// 	return (out ? out : ft_strdup(""));
// }

// char *handle_double_quote(const char *s, int *i, t_env *env)
// {
// 	char	*res;
// 	char	*part;

// 	res = NULL;
// 	(*i)++;
// 	while (s[*i] && s[*i] != '"')
// 	{
// 		if (s[*i] == '$')
// 			part = expand_dollar(s, i, env);
// 		else
// 		{
// 			int start = *i;
// 			while (s[*i] && s[*i] != '$' && s[*i] != '"')
// 				(*i)++;
// 			part = ft_substr(s, start, *i - start);
// 		}
// 		res = res ? ft_strjoin_free(res, part) : part;
// 	}
// 	if (s[*i] == '"')
// 		(*i)++;
// 	return (res ? res : ft_strdup(""));
// }

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*out;

	if (!s2)
	{
		if (s1)
			return (s1);
		else
			return (ft_strdup(""));
	}
	out = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (out);
}

// char	*handle_single_quote(const char *s, int *i)
// {
// 	int		start;
// 	char	*out;

// 	(*i)++;
// 	start = *i;
// 	while (s[*i] && s[*i] != '\'')
// 		(*i)++;
// 	out = ft_substr(s, start, *i - start);
// 	if (s[*i] == '\'')
// 		(*i)++;
// 	if (out)
// 		return (out);
// 	else
// 		return (ft_strdup(""));
// }

// char	*handle_double_quote(const char *s, int *i, t_env *env)
// {
// 	char	*res;
// 	char	*part;
// 	int		start;

// 	res = NULL;
// 	(*i)++;
// 	while (s[*i] && s[*i] != '"')
// 	{
// 		if (s[*i] == '$')
// 			part = expand_dollar(s, i, env);
// 		else
// 		{
// 			start = *i;
// 			while (s[*i] && s[*i] != '$' && s[*i] != '"')
// 				(*i)++;
// 			part = ft_substr(s, start, *i - start);
// 		}
// 		if (res)
// 			res = ft_strjoin_free(res, part);
// 		else
// 			res = part;
// 	}
// 	if (s[*i] == '"')
// 		(*i)++;
// 	if (res)
// 		return (res);
// 	else
// 		return (ft_strdup(""));
// }

char	*handle_single_quote(const char *s, int *i)
{
	int		start;
	char	*out;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	out = ft_substr(s, start, *i - start);
	if (s[*i] == '\'')
		(*i)++;
	if (out)
		return (out);
	else
		return (ft_strdup(""));
}

static char	*handle_dollar_in_dquote(const char *s, int *i, t_env *env,
		char *res)
{
	char	*part;

	part = expand_dollar(s, i, env);
	if (res)
		return (ft_strjoin_free(res, part));
	else
		return (part);
}

static char	*handle_text_in_dquote(const char *s, int *i, char *res)
{
	char	*part;
	int		start;

	start = *i;
	while (s[*i] && s[*i] != '$' && s[*i] != '"')
		(*i)++;
	part = ft_substr(s, start, *i - start);
	if (res)
		return (ft_strjoin_free(res, part));
	else
		return (part);
}

char	*handle_double_quote(const char *s, int *i, t_env *env)
{
	char	*res;

	res = NULL;
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			res = handle_dollar_in_dquote(s, i, env, res);
		else
			res = handle_text_in_dquote(s, i, res);
	}
	if (s[*i] == '"')
		(*i)++;
	if (res)
		return (res);
	else
		return (ft_strdup(""));
}
