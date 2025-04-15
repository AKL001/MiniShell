/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:56:39 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/15 17:50:36 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// char *expand_string(char *s, t_env *env)
// {
// 	int i;
// 	char q;
// 	char *string;

// 	i = 0;
// 	q = 0;
// 	string = NULL;
// 	if (!env || !s)
// 		return (ft_strdup(""));
// 	while (s[i])
// 	{
// 		if (is_quote(s[i]))
// 		{
// 			get_quote_value(s[i], &q);
// 			string = add_char_to_string(s[i], string);
// 			i++;
// 		}
// 		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
// 		{
// 			string = handle_exit_case((string));
// 			i+=2;
// 		}
// 		else if (s[i] == '$' && (q == '\'' || !ft_isalnum(s[i + 1])))
// 		{
// 			string = add_char_to_string(s[i], string);
// 			i++;
// 		}
// 		else if (s[i] == '$' && q != '\'')
// 			string = add_var_value(string, s, env, &i);
// 		else
// 		{
// 			string = add_char_to_string(s[i], string);
// 			i++;
// 		}
// 	}
// 	return (string);
// }

static void	handle_quote_case(char *s, char *q, int *i, char **string)
{
	get_quote_value(s[*i], q);
	*string = add_char_to_string(s[*i], *string);
	(*i)++;
}

static int	handle_special_cases(char *s, char q, char **string, int i)
{
	if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
	{
		*string = handle_exit_case(*string);
		return (2);
	}
	if (s[i] == '$' && (q == '\'' || !ft_isalnum(s[i + 1])))
	{
		*string = add_char_to_string(s[i], *string);
		return (1);
	}
	return (0);
}

static void	init_expand_vars(int *i, char *q, char **string)
{
	*i = 0;
	*q = 0;
	*string = NULL;
}

char	*expand_string(char *s, t_env *env)
{
	int		i;
	char	q;
	char	*string;
	int		skip;

	if (!env || !s)
		return (ft_strdup(""));
	init_expand_vars(&i, &q, &string);
	while (s[i])
	{
		if (is_quote(s[i]))
			handle_quote_case(s, &q, &i, &string);
		else
		{
			skip = handle_special_cases(s, q, &string, i);
			if (skip)
				i += skip;
			else if (s[i] == '$' && q != '\'')
				string = add_var_value(string, s, env, &i);
			else
				string = add_char_to_string(s[i++], string);
		}
	}
	return (string);
}
