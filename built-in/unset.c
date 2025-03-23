#include "../includes/header.h"

void my_unset(t_env *my_envp, char **args)
{
    t_env *head;
    t_env *prev;

    head = my_envp;
    prev = head;
    while (head)
    {
        if (ft_strncmp(args[1], head->key,ft_strlen(args[1])) == 0)
            break;
        prev = head;
        head = head->next;
    }
    if (ft_strncmp(args[1], head->key,ft_strlen(args[1])) == 0)
    {
        prev->next = head->next;
        free(head->key);
        free(head->value);
        free(head);
    }
}
