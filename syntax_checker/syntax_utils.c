#include "../includes/header.h"


// void increament_quotes(char c,int *s_q_count,int *d_q_count)
// {
//     if (c == '\'')
//         (*s_q_count)++;
//     else if (c == '\"')
//         (*d_q_count)++;
// }
char	*skip_spaces(char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

void handle_q_type(char *input,int i,char *q_type)
{
    if ((input[i] == '\"' || input[i] == '\''))
    {
        if ((*q_type) == input[i])
            (*q_type) = 0;
        else if (!(*q_type))
            (*q_type) = input[i];
    }
}

int is_valid_operator(char *input, int i, char set)
{
    int consecutive;

    consecutive = 0;    
    if (set == '&')
    {
        if (input[i] == '&' && input[i + 1] == '&')
            return 0;
        return 1;
    }
    else if (set == '|')
    {
        if (input[i] == '|' && input[i + 1] == '|')
            return 0;
        if (i > 0 && input[i - 1] == '|')
            return 0;
    }
    return 1;
}

int	check_operator(char *input, int *i, char op)
{
	if (input[*i] == op)
	{
		if (!is_valid_operator(input, *i, op))
			return (1);
		if (input[*i + 1] == op)
			(*i)++;
	}
	return (0);
}

int	check_op_at_end(char *input, int i)
{
	if ((input[i] == '&' || input[i] == '|') && input[i + 1] == '\0')
		return (1);
	return (0);
}