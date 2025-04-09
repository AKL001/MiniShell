#include "../includes/header.h"

char **convert_args_to_array(t_args *args)
{
	int count = 0;
	t_args *temp;
	char **arg_array;

	temp = args;
	while (temp && ++count)
		temp = temp->next;
	arg_array = malloc((count + 1) * sizeof(char *));
	if (!arg_array)
		return (NULL);
	temp = args;
	count = 0;
	while (temp)
	{
		arg_array[count++] = temp->value;
		temp = temp->next;
	}
	arg_array[count] = NULL;
	return (arg_array);
}


// int execute_builtin(t_env *my_envp, char **args)
// {
// 	size_t len;

// 	if (!*args)
// 		return (1);
// 	len = ft_strlen(args[0]);
// 	if (ft_strncmp("env", args[0], len) == 0)
// 		my_env(my_envp);
// 	else if (ft_strncmp("echo", args[0], len) == 0)
// 		my_echo(my_envp, args);
// 	else if (ft_strncmp("export", args[0], len) == 0)
// 		my_export(my_envp, args);
// 	else if (ft_strncmp("unset", args[0], len) == 0)
// 		my_unset(my_envp, args);
// 	else if (ft_strncmp("pwd", args[0], len) == 0)
// 		my_pwd(args);
// 	else if (ft_strncmp("cd", args[0], len) == 0)
// 		my_cd(args);
// 	return (0);
// }
int	execute_builtin(t_command *cmd, t_env **env)
{
	char	*command;
	char	**args_array;

	if (!cmd->args)
		return (0);
	command = cmd->args->value;
	args_array = convert_args_to_array(cmd->args);
	if (!args_array)
		return 0; 
	// if (handle_redirections(cmd) == -1)
	// 	return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (my_echo(*env, args_array),free(args_array),1);
	else if (ft_strcmp(command, "cd") == 0)
		return (my_cd(args_array,env),free(args_array),1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (my_pwd(args_array),free(args_array),1);
	else if (ft_strcmp(command, "export") == 0)
		return (my_export(env,args_array),1);
	else if (ft_strcmp(command, "unset") == 0)
		return (my_unset(env, args_array),1);
	else if (ft_strcmp(command, "env") == 0)
		return (my_env(*env),free(args_array),1);
	// else if (ft_strcmp(command, "exit") == 0)
	// 	return (builtin_exit(cmd->args->next));
	free(args_array);
	return 0;
}

