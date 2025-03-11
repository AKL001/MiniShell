#include "includes/minishell.h"

/*
    TODO
    - Tokenizer -> will tokoniz each word or operator or ... 
    - parser    -> manage them what first exe ?? (we need to check if operators next is op aswell if yes = error)
    - expander  s

*/

int main() {
    // using_history();  // Enable command history

    while (1) {
        char *pwd;
        
        // pwd = getcwd(NULL, 0);
        char* input = readline("minishell$ ");

        if (!input)  // Check for EOF (Ctrl+D)
            break;
        // syntax_checker_and_tokoniz(input);

    }

    return 0;
}
