#include "header.h"


int main(int ac, char *av[], char **envp)
{
    char *cmd;
    char **arg;
    t_env *my_envp;

	my_envp = init_envp(envp);
    while (1)
    {
        cmd = readline("minishell> ");
        if (ft_strncmp("exit",cmd,4) == 0)
            break;
        arg = ft_split(cmd,' ');

        execute_builtin(my_envp, arg);
    }
	return (0);
}