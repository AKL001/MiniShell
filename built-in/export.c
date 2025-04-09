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

static void add_envp_var(t_env **custom_envp, char *key, char *value, int overwrite)
{
    t_env *new_node, *head;

    if (!custom_envp || !key || !value)
        return;
    if (overwrite && *custom_envp && update_env_var(*custom_envp, key, value))
        return;
    if (!overwrite)
    {
        head = *custom_envp;
        while (head)
        {
            if (strcmp(head->key, key) == 0)
                return;
            head = head->next;
        }
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

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !(str[0] == '_' || (str[0] >= 'A' && str[0] <= 'Z')
		|| (str[0] >= 'a' && str[0] <= 'z')))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

void	my_export(t_env **env, char **args)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	if (!args[1])
	{
		print_export(*env);
		g_vars.g_exit_status = 0;
		return ;
	}
	i = 1;
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');    
		if (equal)
		{
			*equal = '\0';
			key = args[i];
			value = equal + 1;
			if (is_valid_identifier(key))
				add_envp_var(env, key, value,1);
			else
			{
				write(2, "export: not a valid identifier\n", 31);
				g_vars.g_exit_status = 1;
				return ;
			}
			*equal = '=';
		}
		else if (is_valid_identifier(args[i]))
			add_envp_var(env, args[i], "",0);
		else
		{
			write(2, "export: not a valid identifier\n", 31);
			g_vars.g_exit_status = 1;
			return ;
		}	
		i++;
	}
	g_vars.g_exit_status = 0;
}
