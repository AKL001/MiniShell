#include "header.h"

t_env *create_new(char *name, char *value)
{
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->name = ft_strdup(name);
    new_node->value = ft_strdup(value);
    new_node->Next = NULL;
    return(new_node);
}

void add_env_var(t_env **my_envp, char *name, char *value)
{
    t_env *new_node, *head;

    if (!my_envp || !name || !value)
        return;

    head = *my_envp;
    while (head) 
    {
        if (strcmp(head->name, name) == 0) {
            free(head->value);
            head->value = strdup(value);
            return;
        }
        head = head->Next;
    }
    new_node = create_new(name, value);
    if (!new_node)
        return;
    if (!*my_envp) 
    {
        *my_envp = new_node;
        return;
    }
    head = *my_envp;
    while (head->Next)
        head = head->Next;
    head->Next = new_node;
}


t_env *init_envp(char **envp)
{
    int i;
    char *equal;
    t_env *my_envp = NULL;

    i = 0;
    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (equal) 
        {
            *equal = '\0';
            add_env_var(&my_envp, envp[i], equal + 1);
            *equal = '=';
        }
        i++;
    }
    return (my_envp);
}
