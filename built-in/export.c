#include "../../includes/header.h"

static int update_env_var(t_env *head, char *name, char *value)
{
    while (head)
    {
        if (strcmp(head->name, name) == 0)
        {
            free(head->value);
            head->value = strdup(value);
            return 1;
        }
        head = head->Next;
    }
    return 0;
}

static void add_envp_var(t_env **my_envp, char *name, char *value)
{
    t_env *new_node, *head;

    if (!my_envp || !name || !value)
        return;
    if (*my_envp && update_env_var(*my_envp, name, value))
        return;
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

void my_export(t_env *my_envp, char **args)
{
    char *equal;

    equal = ft_strchr(args[1], '=');
    if (equal)
    {
        *equal = '\0';
        add_envp_var(&my_envp, args[1], equal + 1);
        *equal = '=';
    }
}
