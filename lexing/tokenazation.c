/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:36:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 10:44:02 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

// t_token	*command_to_tokens(char *cmd)
// {
// 	t_token	*tokens;
// 	int		i;
// 	int		start;
// 	char	quote;
// 	char	*token;
// 	t_token	*new_token;
// 	t_token	*last;

// 	tokens = NULL;
// 	i = 0;
// 	quote = 0;
// 	while (cmd[i])
// 	{
// 		while (is_space(cmd[i]))
// 			i++;
// 		if (!cmd[i])
// 			break ;
// 		start = i;
// 		while (cmd[i])
// 		{
// 			if (!quote && is_quote(cmd[i]))
// 				quote = cmd[i];
// 			else if (quote && cmd[i] == quote)
// 				quote = 0;
// 			else if (!quote && is_space(cmd[i]))
// 				break ;
// 			i++;
// 		}
// 		token = ft_substr(cmd, start, i - start);
// 		if (!token)
// 		{
// 			free_token(tokens);
// 			return (NULL);
// 		}
// 		new_token = create_new_token(token);
// 		free(token);
// 		if (!new_token)
// 		{
// 			free_token(tokens);
// 			return (NULL);
// 		}
// 		if (!tokens)
// 			tokens = new_token;
// 		else
// 		{
// 			last = tokens;
// 			while (last->next)
// 				last = last->next;
// 			last->next = new_token;
// 		}
// 	}
// 	return (tokens);
// }

static void	append_token(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

char	*next_token_str(char *cmd, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (cmd[*i])
	{
		if (!quote && is_quote(cmd[*i]))
			quote = cmd[*i];
		else if (quote && cmd[*i] == quote)
			quote = 0;
		else if (!quote && is_space(cmd[*i]))
			break ;
		(*i)++;
	}
	return (ft_substr(cmd, start, *i - start));
}

t_token	*command_to_tokens(char *cmd)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (cmd[i])
	{
		while (is_space(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		token = next_token_str(cmd, &i);
		if (!token)
			return (free_token(tokens), NULL);
		new_token = create_new_token(token);
		free(token);
		if (!new_token)
			return (free_token(tokens), NULL);
		append_token(&tokens, new_token);
	}
	return (tokens);
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
	if (syntax_checker(trim))
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
