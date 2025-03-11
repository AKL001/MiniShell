#include "../../includes/minishell.h"
#include <stdlib.h>

/*
    *TODO
    - misplaced_operators ;
    - redirection handling ; 
*/
static int unclosed_quotes(char *input)
{
    int i;
    char q_type;

    i = 0;
    q_type = 0;
    while(input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            if (q_type == input[i])
                q_type = 0;
            else if (!q_type)
                q_type = input[i];
        }
        i++;
    }
    return (q_type != 0);
}

static  int unclosed_parentheses(char *input)
{
    int i;
    int para_count;
    int q_type;

    i = -1;
    q_type = 0;
    para_count = 0;
    while(input[++i])
    {
        if(input[i] == '\"' || input[i] == '\'')
        {
            if (q_type == input[i])
                q_type = 0;
            else if (!q_type)
                q_type = input[i];
        }   
        if (input[i] == '(' && !q_type)
            para_count++;
        else if (input[i] == ')' && !q_type)
            para_count--;
    }
    if (para_count != 0)
        return 1;
    return 0;
}

static int	invalid_operators(char *input)
{
	int		i;
	char	q_type;

	if (input[0] == '&' || input[0] == '|')
		return (1);
	i = 0;
	q_type = 0;
	while (input[i])
	{
		handle_q_type(input, i, &q_type);
		if (!q_type)
		{
			if (check_operator(input, &i, '&'))
				return (1);
			if (check_operator(input, &i, '|'))
				return (1);
			if (check_op_at_end(input, i))
				return (1);
		}
		i++;
	}
	return (0);
}

/* redirection checker */
static int	invalid_redirections(char *input)
{
	int		i;
	char	q_type;

	i = 0;
	q_type = 0;
	while (input[i])
	{
        handle_q_type(input, i, &q_type);
		if (!q_type && (input[i] == '>' || input[i] == '<'))
		{
            // send i + 1 to check the next one;
			if (is_valid_redirection(input, i))
				return (1);
			if ((input[i] == '>' && input[i + 1] == '>') ||
				(input[i] == '<' && input[i + 1] == '<'))
				i++;
			if (check_redir_follow(input, i + 1))
				return (1);
		}
		i++;
	}
	return (0);
}



static int syntax_checker(char *input)
{
    if(unclosed_quotes(input))
    {
        // we need to change printf with  ft_putstr_fd()
        printf(RED"unlosed quotes\n"RESET);
        return 1;
    }
    // unclosed parantheses
    if(unclosed_parentheses(input))
    {
        // we need to change printf with  ft_putstr_fd()
        printf(RED "unlosed parentheses\n"RESET);
        return 1;
    }
     // Check for invalid operators
    if (invalid_operators(input))
    {
        // we need to change printf with  ft_putstr_fd()
        printf(RED "syntax error near unexpected token\n" RESET);
        return 1;
    }
    // invalid redirections
    if(invalid_redirections(input))
    {
        // we need to change printf with  ft_putstr_fd()
        printf(RED "syntax error : invalid redirection\n" RESET);
        return 1;
    }
    return 0;
}

int syntax_checker_and_tokoniz(char *input)
{
    char *input_trim;
    t_token *tokens;

    input_trim = ft_strtrim(input, " \v\t\n\r");
    free(input);
    if (!input_trim)
        return 1;
    if(syntax_checker(input_trim))
    {
        free(input_trim);
        return 1;
    }
    // condition for tokonizer
    tokens = tokeniz_input(input_trim);
    free(input_trim);
    printf_tokenizer(tokens);
    return 0;
}
