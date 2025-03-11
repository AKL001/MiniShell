#include "../../includes/minishell.h"


void printf_tokenizer(t_token *tokens)
{
    while (tokens)
    {
        printf("[Type: %d] Value: '%s'\n", tokens->type, tokens->value);
        tokens = tokens->next;
    }
}