/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:22:04 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/18 10:30:36 by ael-aiss         ###   ########.fr       */
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
	while (ft_isspace(input[start]))
		start++;
	end = ft_strlen(input) - 1;
	while (end >= start && ft_isspace(input[end]))
		end--;
	if (start > end)
		str = ft_strdup("");
	else
		str = ft_substr(input, start, end - start + 1);
	if (!str)
		return (ft_strdup(""));
	return (str);
}

static	void	initialisation_vars(char **string, int *i, char *q)
{
	*q = 0;
	*i = -1;
	*string = NULL;
}

char	*remove_quotes(char *trim)
{
	char	*string;
	int		i;
	char	q;

	if (!trim)
		return (ft_strdup(""));
	initialisation_vars(&string, &i, &q);
	while (trim[++i])
	{
		if (is_quote(trim[i]))
		{
			if (q == 0)
				q = trim[i];
			else if (q == trim[i])
				q = 0;
			else
				string = add_char_to_string(trim[i], string);
		}
		else
			string = add_char_to_string(trim[i], string);
	}
	if (!string)
		return (free(trim), ft_strdup(""));
	return (free(trim), string);
}

void	remove_quotes_main(t_token *tokens)
{
	char	*remove;
	int		is_delim;

	is_delim = 0;
	while (tokens)
	{
		if (is_delim && tokens->type == TOKEN_WORD)
			is_delim = 0;
		else
		{
			if (tokens->type == TOKEN_HEREDOC)
				is_delim = 1;
			else
			{
				remove = remove_quotes(tokens->value);
				tokens->value = remove;
			}
		}
		tokens = tokens->next;
	}
}
