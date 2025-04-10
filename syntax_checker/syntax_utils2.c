/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:14:13 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/10 19:14:16 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_valid_redirection(char *input, int i)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>' && input[i + 2] != '>')
			return (0);
		else if (input[i + 1] != '>')
			return (0);
		return (1);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<' && input[i + 2] != '<')
			return (0);
		else if (input[i + 1] != '<')
			return (0);
		return (1);
	}
	return (1);
}

int	check_redir_follow(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (!input[i] || input[i] == '>' || input[i] == '<' || input[i] == '|')
		return (1);
	return (0);
}
