#include "includes/minishell.h"

/*
    TODO
    - Tokenizer -> will tokoniz each word or operator or ... 
    - parser    -> manage them what first exe ?? (we need to check if operators next is op aswell if yes = error)
    - expander  s

*/

int main(int c, char **av, char **env)
{
    t_env *my_envp = NULL;
    t_token *tokens;
    my_envp = init_envp(env);
    while (1) {
        char *pwd;
        
        char* input = readline("minishell$ ");

        if (!input)
            break;
        tokens = syntax_checker_and_tokoniz(input);
        // execute_builtin(my_envp , str);
        // printf_tokenizer(tokens);
        
    }

    return 0;
}
