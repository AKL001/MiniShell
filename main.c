/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:52:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 18:53:39 by ael-aiss         ###   ########.fr       */
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
	ft_memset(&g_vars, 0, sizeof(t_vars));
	if (!isatty(1) || !isatty(0))
		return (free_env(custom_env), 0);
	while (1)
	{
		setup_parent_signals();
		g_vars.in_child = 0; 
		cmd = readline("shell~$ ");
		if (!cmd)
		{
			printf("exit\n");
			break ;
		}
		g_vars.in_child = 1; 
		if (*cmd)
			add_history(cmd);
		tokens = tokenazation(cmd);
		free(cmd);
		exec_cmd = parse_token(tokens , custom_env);
		// print_commands(exec_cmd);	
		execute_command_line(exec_cmd,custom_env);
		// printf("---------\033[1;32mg_exit_status => \033[1;36m%d\033[0m--------\n", g_vars.g_exit_status);
		free_commands(exec_cmd);
	}
	clear_history();
	free_env(custom_env);
	return (0);
}


// int main(int argc, char *args[], char **envp)
// {
//     char        cmd[1024];  // Buffer for scanf input
//     t_token     *tokens;
//     t_env       *custom_env;
//     t_command   *exec_cmd;
    
//     argc++;
//     (*args) = NULL;

//     custom_env = init_envp(envp);
//     ft_memset(&g_vars, 0, sizeof(t_vars));
    
//     if (!isatty(1) || !isatty(0))
//         return (free_env(custom_env), 0);

//     while (1)
//     {
//         setup_parent_signals();
//         g_vars.in_child = 0;
        
//         // Replace readline with scanf that reads everything including spaces
//         printf("shell~$ ");
//         if (scanf("%1023[^\n]", cmd) != 1)
//         {
//             printf("exit\n");
//             while (getchar() != '\n');  // Clear input buffer
//             break;
//         }
//         while (getchar() != '\n');  // Clear the newline from buffer

//         g_vars.in_child = 1;
//         if (*cmd)
//             add_history(cmd);
        
//         tokens = tokenazation(cmd);
//         exec_cmd = parse_token(tokens, custom_env);
//         execute_command_line(exec_cmd, custom_env);
//         free_commands(exec_cmd);
//     }
    
//     clear_history();
//     free_env(custom_env);
//     return (0);
// }