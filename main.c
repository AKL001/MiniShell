#include "header.h"


int main(int ac, char *av[], char **envp)
{
    char *cmd;
    char **arg;

	init_envp(envp);
    while (1)
    {
        cmd = readline("prompt> ");
        if (ft_strncmp("exit",cmd,4) == 0)
            break;
        arg = ft_split(cmd,' ');

        execute_builtin(arg);
    }
	return (0);
}