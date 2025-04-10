#include "../includes/header.h"

static int	is_numeric(const char *str)
{
	int i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


void	my_exit(char **args)
{
	long	exit_code;

	printf("exit\n");
	if (args[1] && args[2])
	{
		error_message("exit: too many arguments\n", 1);
		g_vars.g_exit_status = 1;
		return;
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			error_message("exit: numeric argument required\n", 2);
            exit(2);
		}
		exit_code = ft_atol(args[1]);
        exit(exit_code % 256);
	}
    exit(0);
}
