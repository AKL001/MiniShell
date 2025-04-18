/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 04:36:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/18 10:31:36 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	get_quote_value(char c, char *q)
{
	if ((*q) == 0)
		(*q) = c;
	else if (*q == c)
		(*q) = 0;
}

void	handle_normal_string(t_token **tokens, int *i, char *cmd, char *q)
{
	char	*value;

	value = NULL;
	if (cmd[*i] && is_quote(cmd[*i]))
	{
		value = add_char_to_string(cmd[*i], value);
		(*i)++;
	}
	while (cmd[*i] && ((*q) || !is_split_op(cmd[*i])))
	{
		if (is_quote(cmd[*i]))
		{
			get_quote_value(cmd[*i], q);
			value = add_char_to_string(cmd[*i], value);
		}
		else
			value = add_char_to_string(cmd[*i], value);
		(*i)++;
	}
	if (value && *value)
	{
		add_new_value_to_tokens(tokens, value);
		free(value);
	}
}

t_token	*command_to_tokens(char *cmd)
{
	t_token	*tokens;
	char	quote;
	int		i;

	tokens = NULL;
	quote = 0;
	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '"'))
			quote = cmd[i];
		if (is_split_op(cmd[i]) && quote == 0)
			add_special_operator(&tokens, &i, cmd);
		else
			handle_normal_string(&tokens, &i, cmd, &quote);
	}
	return (tokens);
}

t_token	*tokenazation(char *input, t_env *env)
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
		g_vars.g_exit_status = 2;
		return (NULL);
	}
	if (!check_unclosed_quotes(input))
	{
		free(trim);
		g_vars.g_exit_status = 2;
		printf("uncloused quotes\n");
		return (NULL);
	}
	tokens = command_to_tokens(trim);
	expand_tokens(&tokens, env);
	free(trim);
	return (tokens);
}
