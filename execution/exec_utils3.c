#include "../includes/header.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args->value)
		return (0);
	return (ft_strcmp(cmd->args->value, "cd") == 0
		|| ft_strcmp(cmd->args->value, "echo") == 0
		|| ft_strcmp(cmd->args->value, "env") == 0
		|| ft_strcmp(cmd->args->value, "exit") == 0
		|| ft_strcmp(cmd->args->value, "export") == 0
		|| ft_strcmp(cmd->args->value, "pwd") == 0
		|| ft_strcmp(cmd->args->value, "unset") == 0);
}

void	restore_std_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}

int	restore_and_exit(int saved_fds[2], int exit_code)
{
	restore_std_fds(saved_fds);
	return (exit_code);
}

int	exec_builtin(t_command *cmd, int *p_fds)
{
	if (handle_redirections(cmd) == -1)
		return (restore_and_exit(p_fds, 1));
	if (execute_builtin(cmd, &cmd->env))
		return (restore_and_exit(p_fds, 1));
	restore_std_fds(p_fds);
	return (0);
}