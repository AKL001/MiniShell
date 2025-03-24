/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:52:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/24 07:22:05 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

int	main(int argc, char *args[], char **envp)
{
	char		*cmd;
	t_env *custom_env;
	argc++;
	args = NULL;

	custom_env  = init_envp(envp);

	t_command	*exec_cmd;

	while (1)
	{
		cmd = readline("shell~$ ");
		if (!cmd)
			break ;
		add_history(cmd);
		exec_cmd = parse_token(cmd, custom_env);
		if (!exec_cmd)
			return(NULL);

		execute_cmd(exec_cmd);
		print_commands(exec_cmd);
		free_commands(exec_cmd);
	}
	clear_history();
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
