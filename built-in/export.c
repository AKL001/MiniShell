#include "../includes/header.h"

static int update_env_var(t_env *head, char *key, char *value)
{
    while (head)
    {
        if (strcmp(head->key, key) == 0)
        {
            free(head->value);
            head->value = strdup(value);
            return 1;
        }
        head = head->next;
    }
    return 0;
}

static void add_envp_var(t_env **custom_envp, char *key, char *value)
{
    t_env *new_node, *head;

    if (!custom_envp || !key || !value)
        return;
    if (*custom_envp && update_env_var(*custom_envp, key, value))
        return;
    new_node = create_new(key, value);
    if (!new_node)
        return;
    if (!*custom_envp)
    {
        *custom_envp = new_node;
        return;
    }
    head = *custom_envp;
    while (head->next)
        head = head->next;
    head->next = new_node;
}

void my_export(t_env *custom_envp, char **args)
{
    char *equal;

    equal = ft_strchr(args[1], '=');
    if (equal)
    {
        *equal = '\0';
        add_envp_var(&custom_envp, args[1], equal + 1);
        *equal = '=';
    }
}
