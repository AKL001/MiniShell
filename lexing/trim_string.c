/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:22:04 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/16 21:29:33 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// char	*trim_whitespace(char *input)
// {
// 	int		start;
// 	int		end;
// 	char	*str;

// 	if (!input || !*input)
// 		return (NULL);
// 	start = 0;
// 	while (input[start] == '\t' || input[start] == ' ')
// 		start++;
// 	end = ft_strlen(input) - 1;
// 	while (input[end] == ' ' || input[end] == '\t')
// 		end--;
// 	if (start > end)
// 		str = ft_strdup("");
// 	else
// 		str = ft_substr(input, start, end - start + 1);
// 	return (str);
// }

char	*trim_whitespace(char *input, t_env *env)
{
	int		start;
	int		end;
	char	*str;
	char	*expand;

	if (!input || !*input)
		return (NULL);
	start = 0;
	while (input[start] == '\t' || input[start] == ' ')
		start++;
	end = ft_strlen(input) - 1;
	while (end >= start && (input[end] == ' ' || input[end] == '\t'))
		end--;
	if (start > end)
		str = ft_strdup("");
	else
		str = ft_substr(input, start, end - start + 1);
	// expand = expand_string(str, env);
	// free(str);
	if (!str)
		return (ft_strdup(""));
	return (str);
}

char	*remove_quotes(char *trim)
{
	char	*string;
	int		i;
	char	q;

	string = NULL;
	i = -1;
	q = 0;
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

void remove_quotes_main(t_token *tokens)
{
	
	while (tokens)
	{
		tokens->value= remove_quotes(tokens->value);;
		tokens = tokens->next;
	}
}