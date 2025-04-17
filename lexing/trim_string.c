/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:22:04 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/17 09:22:32 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*trim_whitespace(char *input, t_env *env)
{
	int		start;
	int		end;
	char	*str;
	char	*expand;

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

	if (!trim)
		return (ft_strdup(""));
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
	char	*remove;
	int		is_delim;

	is_delim = 0;
	while (tokens)
	{
		// if (tokens->type )
		// tokens->value= remove_quotes(tokens->value);;
		// tokens = tokens->next;
		if (is_delim && tokens->type == TOKEN_WORD)
			is_delim = 0;
		else
		{
			if (tokens->type == TOKEN_HEREDOC)
				is_delim = 1;
			else
			{
				remove = remove_quotes(tokens->value);
				// free(tokens->value);
				tokens->value = remove;
			}
		}
		tokens = tokens->next;
	}
}

// cat | << | ""eof

// void	expand_tokens(t_token **tokens, t_env *env)
// {
// 	t_token	*head;
// 	char	*expand;
// 	int		is_delim;

// 	head = *tokens;
// 	is_delim = 0;
// 	while (head)
// 	{
// 		if (is_delim && head->type == TOKEN_WORD)
// 			is_delim = 0;
// 		else
// 		{
// 			if (head->type == TOKEN_HEREDOC)
// 				is_delim = 1;
// 			else
// 			{
// 				expand = remove_quotes(tokens->value);
// 				free(head->value);
// 				head->value = expand;
// 			}
// 		}
// 		head = head->next;
// 	}
// }