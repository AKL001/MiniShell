/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:36:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:40:48 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_token	*command_to_tokens(char *cmd)
{
	t_token	*tokens;
	int		i;
	char	*value;

	i = 0;
	tokens = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			value = handle_quote(cmd, &i);
		else if (is_operator(cmd[i]))
			value = handle_operator(cmd, &i);
		else
			value = handle_word(cmd, &i);
		if (!value)
		{
			free_token(tokens);
			return (NULL);
		}
		add_new_token(&tokens, value);
		free(value);
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
