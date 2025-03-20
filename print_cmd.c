/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:36:37 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/20 00:40:54 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

void	print_commands(t_command *cmdd)
{
	t_command	*cmd;
	int			cmd_idx;
	t_args		*argv;
	t_redir		*r;
	const char	*type;

	cmd = cmdd;
	cmd_idx = 0;
	while (cmd)
	{
		printf("Command %d:\n", ++cmd_idx);
		// Print arguments
		printf("  Arguments: ");
		argv = cmd->args;
		while (argv && argv->value != NULL)
		{
			printf("[%s]", argv->value);
			argv = argv->next;
		}
		printf("\n");
		// Print redirections
		printf("  Redirections:\n");
		r = cmd->redirections;
		while (r)
		{
			type = "UNKNOWN";
			switch (r->type)
			{
			case REDIR_IN:
				type = "<";
				break ;
			case REDIR_OUT:
				type = ">";
				break ;
			case REDIR_APPEND:
				type = ">>";
				break ;
			case REDIR_HEREDOC:
				type = "<<";
				break ;
			}
			printf("%s %s\n", type, r->filename);
			r = r->next; // Move to the next redirection
		}
		cmd = cmd->next; // Move to the next command
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("Token Value: %s\n", token->value);
		switch (token->type)
		{
		case TOKEN_WORD:
			printf("Type: TOKEN_WORD\n");
			break ;
		case TOKEN_PIPE:
			printf("Type: TOKEN_PIPE\n");
			break ;
		case TOKEN_REDIRECT_IN:
			printf("Type: TOKEN_REDIRECT_IN\n");
			break ;
		case TOKEN_REDIRECT_OUT:
			printf("Type: TOKEN_REDIRECT_OUT\n");
			break ;
		case TOKEN_APPEND:
			printf("Type: TOKEN_APPEND\n");
			break ;
		case TOKEN_HEREDOC:
			printf("Type: TOKEN_HEREDOC\n");
			break ;
		default:
			printf("Type: Unknown\n");
		}
		token = token->next;
	}
}
