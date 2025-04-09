/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:36:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/09 20:45:50 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// t_token	*command_to_tokens(char *cmd)
// {
// 	t_token	*tokens;
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	tokens = NULL;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' || cmd[i] == '"')
// 			value = handle_quote(cmd, &i);
// 		if (is_operator(cmd[i]))
			// value = handle_operator(cmd, &i);
// 		else
// 			value = handle_word(cmd, &i);
// 		if (!value)
// 		{
// 			free_token(tokens);
// 			return (NULL);
// 		}
// 		add_new_token(&tokens, value);
// 		free(value);
// 	}
// 	return (tokens);
// }

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

t_token	*command_to_tokens(char *cmd)
{
	t_token	*tokens = NULL;
	int		i = 0;
	int		start;
	char	quote = 0;

	while (cmd[i])
	{
		while (is_space(cmd[i]))
			i++;
		if (!cmd[i])
			break;
		start = i;
		while (cmd[i])
		{
			if (!quote && is_quote(cmd[i]))
				quote = cmd[i];
			else if (quote && cmd[i] == quote)
				quote = 0;
			else if (!quote && is_space(cmd[i]))
				break;
			i++;
		}
		char *token = ft_substr(cmd, start, i - start);
		if (!token)
		{
			free_token(tokens);
			return NULL;
		}
		t_token *new_token = create_new_token(token);
		free(token);
		if (!new_token)
		{
			free_token(tokens);
			return NULL;
		}
		if (!tokens)
			tokens = new_token;
		else
		{
			t_token *last = tokens;
			while (last->next)
				last = last->next;
			last->next = new_token;
		}
	}
	return tokens;
}

t_token	*tokenazation(char *input)
{
	char	*trim;
	t_token	*tokens;

	if (!input)
		return (NULL);
	trim = trim_whitespace(input);
	if (!trim)
		return (NULL);
	if(syntax_checker(trim))
    {
        free(trim);
        return (NULL);
    }
	if (!check_unclosed_quotes(input))
	{
		free(trim);
		printf("uncloused quotes\n");
		return (NULL);
	}
	tokens = command_to_tokens(trim);
	free(trim);
	return (tokens);
}
