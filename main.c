/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:52:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/17 13:54:11 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"
#include "libft/libft.h"

// int g_exit_status;

t_vars		g_vars;

static void	print_args(t_args *args)
{
	printf("Arguments: ");
	while (args)
	{
		printf("[%s]", args->value);
		args = args->next;
	}
	printf("\n");
}

static void	print_redirections(t_redir *redirections)
{
	printf("Redirections: ");
	while (redirections)
	{
		printf("%d:%s ", redirections->type, redirections->filename);
		redirections = redirections->next;
	}
	printf("\n");
}

void	print_command(t_command *cmd)
{
	int	cmd_num;

	cmd_num = 1;
	while (cmd)
	{
		printf("Command %d:\n", cmd_num++);
		print_args(cmd->args);
		print_redirections(cmd->redirections);
		cmd = cmd->next;
		if (cmd)
		{
			printf("---\n");
		}
	}
}
void	print_token_list(t_token *head)
{
	t_token	*current;
	int		index;

	current = head;
	index = 0;
	while (current)
	{
		printf("Token [%d]:\n", index);
		printf("  Value: [%s]\n", current->value);
		current = current->next;
		index++;
	}
}

char	**create_default_env(void)
{
	char	**env;
	char	*cwd;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	cwd = getcwd(NULL, 0);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = ft_strdup("PATH=/usr/bin:/bin");
	env[4] = NULL;
	free(cwd);
	return (env);
}


static int	init_shell_environment(t_env **env, char **envp)
{
	char 	**default_env;

	default_env = NULL;
	if (!envp || !*envp)
	{
		default_env = create_default_env();
		if (!default_env)
			return (0);
		envp = default_env;
	}
	*env = init_envp(envp);
	if (!*env)
		return (0);
	ft_memset(&g_vars, 0, sizeof(t_vars));
	if (!isatty(0) || !isatty(1))
	{
		free_env(*env);
		return (0);
	}
	return (1);
}

static void	process_input_loop(t_env *env)
{
	char		*cmd;
	t_token		*tokens;
	t_command	*exec_cmd;

	while (1)
	{
		setup_parent_signals();
		g_vars.in_child = 0;
		cmd = readline("minishell$ ");
		if (!cmd)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		g_vars.in_child = 1;
		if (*cmd)
			add_history(cmd);
		tokens = tokenazation(cmd,env);
		print_token_list(tokens);
		free(cmd);
		exec_cmd = parse_token(tokens, env);
		print_command(exec_cmd);
		execute_command_line(exec_cmd, env);
		free_commands(exec_cmd);
	}
}

int	main(int argc, char *args[], char **envp)
{
	t_env	*custom_env;

	(void)argc;
	(void)args;
	if (!init_shell_environment(&custom_env, envp))
		return (1);
	process_input_loop(custom_env);
	clear_history();
	free_env(custom_env);
	return (g_vars.g_exit_status);
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
//             break ;
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
