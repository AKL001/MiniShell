/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:30:34 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:50:07 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_redirection(t_token_type token_type)
{
	if (token_type == TOKEN_REDIRECT_IN
		|| token_type == TOKEN_REDIRECT_OUT
		|| token_type == TOKEN_APPEND
		|| token_type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_redir_type	get_redirection_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIRECT_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIRECT_OUT)
		return (REDIR_OUT);
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN);
}
