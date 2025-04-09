/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:52:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/09 23:36:16 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"
#include "libft/libft.h"

// int g_exit_status;

t_vars 		g_vars;   

int	main(int argc, char *args[], char **envp)
{
	char		*cmd;
	t_token		*tokens;
	t_env 		*custom_env;
	t_command	*exec_cmd;
	argc++;
	(*args) = NULL;

	custom_env  = init_envp(envp);
	// init the global var ;
	ft_memset(&g_vars, 0, sizeof(t_vars));
	if (!isatty(1) || !isatty(0))
		return (free(custom_env), 0);
	while (1)
	{
		cmd = readline("shell~$ ");
		if (!cmd)
			break ;
		add_history(cmd);
		tokens = tokenazation(cmd);
		free(cmd);
		exec_cmd = parse_token(tokens , custom_env);
		// if (!exec_cmd)
		// 	return(1);
		// execute_cmd(exec_cmd);
		// print_commands(exec_cmd);
		execute_command_line(exec_cmd,custom_env);
		// printf("---------\033[1;32mg_exit_status => \033[1;36m%d\033[0m--------\n", g_vars.g_exit_status);
		free_commands(exec_cmd);
	}
	clear_history();
	free(custom_env);
	return (0);
}
