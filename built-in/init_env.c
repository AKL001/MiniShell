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

void add_env_var(t_env **custom_envp, char *key, char *value)
{
    t_env *new_node, *head;

    if (!custom_envp || !key || !value)
        return;
    head = *custom_envp;
    while (head)
    {
        if (ft_strcmp(head->key, key) == 0)
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

// t_env *init_envp(char **envp)
// {
//     int i;
//     char *equal;
//     t_env *custom_envp = NULL;

//     i = 0;
//     while (envp[i])
//     {
//         equal = ft_strchr(envp[i], '=');
//         if (equal)
//         {
//             *equal = '\0';
//             add_env_var(&custom_envp, envp[i], equal + 1);
//             // *equal = '=';
//         }
//         i++;
//     }
//     return (custom_envp);
// }

t_env *init_envp(char **envp)
{
    int i;
    char *equal;
    char *key;
    char *entry;
    t_env *custom_envp = NULL;

    i = 0;
    while (envp[i])
    {
        entry = ft_strdup(envp[i]); 
        if (!entry)
            return (NULL);
        equal = ft_strchr(entry, '=');
        if (equal)
        {
            *equal = '\0';
            key = entry;
            add_env_var(&custom_envp, key, equal + 1);
        }
        free(entry);
        i++;
    }
    return (custom_envp);
}

// t_env *init_envp(char **envp)
// {
//     int     i;
//     char    *equal;
//     char    *key;
//     char    *value;
//     char    *entry;
//     t_env   *custom_envp = NULL;

//     i = 0;
//     while (envp[i])
//     {
//         entry = ft_strdup(envp[i]);
//         if (!entry)
//             return (NULL);
//         equal = ft_strchr(entry, '=');
//         if (equal)
//         {
//             *equal = '\0';
//             key = ft_strdup(entry);         
//             value = ft_strdup(equal + 1);   
//             printf("[%s] [%s]\n",key,value);
//             add_env_var(&custom_envp, key, value);
//             free(key);
//             free(value);
//         }
//         free(entry); // safe to free now
//         i++;
//     }
//     return (custom_envp);
// }
