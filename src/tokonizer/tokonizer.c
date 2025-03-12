#include "../../includes/minishell.h"


void handle_special_characters(char **input, t_token **tokens)
{
    if (**input == '>')
    {
        if (*(*input + 1) == '>')
        {
            add_token_to_list(tokens, new_token(T_REDIR_APPEND, ">>"));
            (*input)++;
        }
        else
            add_token_to_list(tokens, new_token(T_REDIR_OUT, ">"));
    }
    else if (**input == '<')
    {
        if (*(*input + 1) == '<')
        {
            add_token_to_list(tokens, new_token(T_REDIR_HEREDOC, "<<"));
            (*input)++;
        }
        else
            add_token_to_list(tokens, new_token(T_REDIR_IN, "<"));
    }
    else if (**input == '&')
    {
        if (*(*input + 1) == '&')
        {
            add_token_to_list(tokens, new_token(T_AND, "&&"));
            (*input)++;
        }
    }
    else if (**input == '|')
    {
        if (*(*input + 1) == '|')
        {
            add_token_to_list(tokens, new_token(T_OR, "||"));
            (*input)++;
        }
        else
            add_token_to_list(tokens, new_token(T_PIPE, "|"));
    }
    else if (**input == '(')
    {
        add_token_to_list(tokens, new_token(T_OPEN_PAREN, "("));
    }
    else if (**input == ')')
    {
        add_token_to_list(tokens, new_token(T_CLOSE_PAREN, ")"));
    }
    (*input)++;
}
void handle_word(char **input, t_token **tokens)
{
    char *start;
    char quote;
    char buffer[1024];
    int i = 0;

    start = *input;
    while (**input && !ft_strchr(WHITESPACES "<>|&()", **input))
    {
        if (**input == '\"' || **input == '\'')
        {
            quote = **input;
            (*input)++;
            while (**input && **input != quote)
            {
                buffer[i++] = **input;
                (*input)++;
            }
            if (**input == quote)
                (*input)++;
        }
        else
        {
            buffer[i++] = **input;
            (*input)++;
        }
    }
    buffer[i] = '\0';
    if (i > 0)
        add_token_to_list(tokens, new_token(T_WORD, buffer));
}

t_token *tokeniz_input(char *input)
{
    t_token *token;

    token = NULL;
    while(*input)
    {
        while(*input && ft_strchr(WHITESPACES, *input))
            input++;
        if (ft_strchr("><&|)(", *input))
            handle_special_characters(&input,&token);
        else
            handle_word(&input, &token);
    }
    return token;
}
