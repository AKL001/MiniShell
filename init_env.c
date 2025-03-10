#include "header.h"

void add_env_var(char *name, char *value)
{
    t_env *new_var;
    t_env *head;
    
    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->Next = NULL;
    if (!my_envp)
    {
        my_envp = new_var;
        return ;
    }
    head = my_envp;
        while (head->Next)
            head = head->Next;    
    head->Next = new_var;
}

void init_envp(char **envp)
{
    int i;
    char *equal;

    i = 0;
    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (equal) 
        {
            *equal = '\0';
            add_env_var(envp[i], equal + 1);
            *equal = '=';
        }
        i++;
    }
}
