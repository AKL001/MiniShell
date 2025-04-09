#include "../includes/header.h"

// void my_unset(t_env *custom_envp, char **args)
// {
//     t_env *head;
//     t_env *prev;

//     head = custom_envp;
//     prev = head;
//     while (head)
//     {
//         if (ft_strncmp(args[1], head->key,ft_strlen(args[1])) == 0)
//             break;
//         prev = head;
//         head = head->next;
//     }
//     if (ft_strncmp(args[1], head->key,ft_strlen(args[1])) == 0)
//     {
//         prev->next = head->next;
//         free(head->key);
//         free(head->value);
//         free(head);
//     }
// }


void	my_unset(t_env **env, char **args)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		cur = *env;
		prev = NULL;
		while (cur)
		{
			if (ft_strcmp(args[i], cur->key) == 0)
			{
				tmp = cur;
				if (!prev)
					*env = cur->next;
				else
					prev->next = cur->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	g_vars.g_exit_status = 0;
}
