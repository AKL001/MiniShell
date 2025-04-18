/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:12:55 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 19:12:56 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**convert_args_to_array(t_args *args)
{
	int		count;
	t_args	*temp;
	char	**arg_array;

	count = 0;
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
		arg_array[count++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	arg_array[count] = NULL;
	return (arg_array);
}

int	execute_builtin(t_command *cmd, t_env **env)
{
	char	*command;
	char	**args_array;

	if (!cmd->args)
		return (0);
	command = cmd->args->value;
	args_array = convert_args_to_array(cmd->args);
	if (!args_array)
		return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (my_echo(*env, args_array), free_array(args_array), 1);
	else if (ft_strcmp(command, "cd") == 0)
		return (my_cd(args_array, env), free_array(args_array), 1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (my_pwd(*env), free_array(args_array), 1);
	else if (ft_strcmp(command, "export") == 0)
		return (my_export(env, args_array), free_array(args_array), 1);
	else if (ft_strcmp(command, "unset") == 0)
		return (my_unset(env, args_array), free_array(args_array), 1);
	else if (ft_strcmp(command, "env") == 0)
		return (my_env(*env), free_array(args_array), 1);
	else if (ft_strcmp(command, "exit") == 0)
		return (my_exit(args_array,*env), free_array(args_array), 1);
	free_array(args_array);
	return (0);
}
