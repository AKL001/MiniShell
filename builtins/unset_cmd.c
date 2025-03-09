#include "header.h"

int check_var(char *string)
{
    char *var_value;

    if (string[0] == '$')
    {
        var_value = get_var_value(string);
        if (var_value)
            printf("%s", var_value);
        return(1);
    }
    return(0);
}

void ft_echo(char **strings)
{
    int i;
    int new_line;

    i = 1;
    new_line = 0;
    if (strings[i] && ft_strcmp(strings[1], "-n") == 0)
    {
        new_line = 1;
        i++;
    }
    while (strings[i])
    {
        if (!check_var(strings[i]));
            printf("%s", strings[i]);
        if (strings[i + 1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
    return (0);
}
