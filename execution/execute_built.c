#include "../includes/header.h"

int	execute_commands(t_command *cmd_list, t_shell *shell)
{
	int			saved_stdin;
	int			saved_stdout;
	int			exit_status;

	if (!cmd_list)
		return (0);
	
	/* Save original stdin/stdout for restoration after execution */
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup"), 1);
	
	/* Execute the command pipeline */
	exit_status = execute_pipeline(cmd_list, shell);
	
	/* Restore original stdin/stdout */
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	
	shell->exit_status = exit_status;
	return (exit_status);
}