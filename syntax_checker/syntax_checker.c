/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:14:06 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 19:14:07 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	invalid_operators(char *input)
{
	int		i;
	char	q_type;

	if (input[0] == '&' || input[0] == '|')
		return (1);
	i = 0;
	q_type = 0;
	while (input[i])
	{
		handle_q_type(input, i, &q_type);
		if (!q_type)
		{
			if (check_operator(input, &i, '&'))
				return (1);
			if (check_operator(input, &i, '|'))
				return (1);
			if (check_op_at_end(input, i))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	invalid_redirections(char *input)
{
	int		i;
	char	q_type;

	i = 0;
	q_type = 0;
	while (input[i])
	{
		handle_q_type(input, i, &q_type);
		if (!q_type && (input[i] == '>' || input[i] == '<'))
		{
			if (is_valid_redirection(input, i))
				return (1);
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
				i++;
			if (check_redir_follow(input, i + 1))
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_checker(char *input)
{
	if (invalid_operators(input))
	{
		printf(RED "syntax error near unexpected token\n" RESET);
		return (1);
	}
	if (invalid_redirections(input))
	{
		printf(RED "syntax error : invalid redirection\n" RESET);
		return (1);
	}
	return (0);
}
