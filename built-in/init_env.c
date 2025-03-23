#include "../includes/header.h"

t_env *create_new(char *key, char *value)
{
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    return (new_node);
}

void add_env_var(t_env **my_envp, char *key, char *value)
{
    t_env *new_node, *head;

    if (!my_envp || !key || !value)
        return;
    head = *my_envp;
    while (head)
    {
        if (ft_strncmp(head->key, key, ft_strlen(key)) == 0)
        {
            free(head->value);
            head->value = ft_strdup(value);
            return;
        }
        head = head->next;
    }
    new_node = create_new(key, value);
    if (!new_node)
        return;
    if (!*my_envp)
    {
        *my_envp = new_node;
        return;
    }
    head = *my_envp;
    while (head->next)
        head = head->next;
    head->next = new_node;
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
