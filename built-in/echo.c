#include "../includes/header.h"

char *get_var_value(t_env *my_envp,char *key)
{
	t_env *head;
	int len;
	char *var_value;

	len = ft_strlen(key);
	head = my_envp;
	while (head)
	{
		if (ft_strncmp(key,head->key,len) == 0)
		{
			var_value = ft_strdup(head->value);
			return(var_value);
		}
		head = head->next;
	}
	return (NULL);
}

int check_var(t_env *my_envp,char *key)
{
	char *var_value;

	if (key[0] == '$')
	{
		var_value = get_var_value(my_envp, key + 1);
		if (var_value)
			printf("%s", var_value);
		return(1);
	}
	return(0);
}

int my_echo(t_env *my_envp,char **args)
{
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	if (args[i] && ft_strncmp(args[i], "-n", ft_strlen(args[i])) == 0)
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		if (!check_var(my_envp, args[i]))
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

