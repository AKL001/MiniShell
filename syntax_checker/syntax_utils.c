/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:14:21 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 19:14:22 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*skip_spaces(char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

void	handle_q_type(char *input, int i, char *q_type)
{
	if ((input[i] == '\"' || input[i] == '\''))
	{
		if ((*q_type) == input[i])
			(*q_type) = 0;
		else if (!(*q_type))
			(*q_type) = input[i];
	}
}

int	is_valid_operator(char *input, int i, char set)
{
	// int	consecutive;

	// consecutive = 0;
	if (set == '&')
	{
		if (input[i] == '&' && input[i + 1] == '&')
			return (0);
		return (1);
	}
	else if (set == '|')
	{
		if (input[i] == '|' && input[i + 1] == '|')
			return (0);
		if (i > 0 && input[i - 1] == '|')
			return (0);
	}
	return (1);
}

int	check_operator(char *input, int *i, char op)
{
	if (input[*i] == op)
	{
		if (!is_valid_operator(input, *i, op))
			return (1);
		if (input[*i + 1] == op)
			(*i)++;
	}
	return (0);
}

int	check_op_at_end(char *input, int i)
{
	if ((input[i] == '&' || input[i] == '|') && input[i + 1] == '\0')
		return (1);
	return (0);
}
