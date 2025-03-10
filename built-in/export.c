#include "../header.h"


static void add_envp_var(char *name, char *value)
{
    t_env *new_var;
    t_env *head;
    
    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->Next = NULL;
   
    head = my_envp;
        while (head->Next->Next)
            head = head->Next;  
        new_var->Next = head->Next;  
    head->Next = new_var;
}

void my_export(char **args)
{
    char *equal;

    equal = ft_strchr(args[1], '=');
    if (equal)
    {
        *equal = '\0';
        add_envp_var(args[1], equal + 1);
        *equal = '=';
    }
}
