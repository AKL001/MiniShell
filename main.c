/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:52:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/25 23:47:49 by ael-aiss         ###   ########.fr       */
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
		execute_command_line(exec_cmd,custom_env);
		// printf("---------\033[1;32mg_exit_status => \033[1;36m%d\033[0m--------\n", g_vars.g_exit_status);
		// print_commands(exec_cmd);
		free_commands(exec_cmd);
	}
	clear_history();
	free(custom_env);
	return (0);
}

// int main(int c, char **av, char **env)
// {
//     t_env *my_envp = NULL;
//     t_token *tokens;
//     my_envp = init_envp(env);
//     while (1) {
//         char *pwd;
        
//         char* input = readline("minishell$ ");

//         if (!input)
//             break;
//         tokens = syntax_checker_and_tokoniz(input);
//         // execute_builtin(my_envp , str);
//         // printf_tokenizer(tokens);
        
//     }

//     return 0;
// }
