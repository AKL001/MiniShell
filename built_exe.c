#include "header.h"

int execute_builtin(char **args)
{
	size_t len;

	if (!*args)
		return (1);
	len = ft_strlen(args[0]);
	if (ft_strncmp("env", args[0], len) == 0)
		my_env();
	else if (ft_strncmp("echo", args[0], len) == 0)
		my_echo(args);
	else if (ft_strncmp("export", args[0], len) == 0)
		my_export(args);
	else if (ft_strncmp("unset", args[0], len) == 0)
		my_unset(args);
	return (0);
}
