#include "../includes/header.h"

char *get_var_value(t_env *custom_envp,char *key)
{
	t_env *head;
	int len;
	char *var_value;

	len = ft_strlen(key);
	head = custom_envp;
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

// int check_var(t_env *custom_envp,char *key)
// {
// 	char *var_value;

// 	if (key[0] == '$')
// 	{
// 		var_value = get_var_value(custom_envp, key + 1);
// 		if (var_value)
// 			printf("%s", var_value);
// 		return(1);
// 	}
// 	return(0);
// }

// int my_echo(t_env *custom_envp,char **args)
// {
// 	int i;
// 	int new_line;

// 	i = 1;
// 	new_line = 1;
// 	if (args[i] && ft_strncmp(args[i], "-n", ft_strlen(args[i])) == 0)
// 	{
// 		new_line = 0;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		// if (!check_var(custom_envp, args[i]))$HO''ME
// 		printf("%s", args[i]);
// 		if (args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (new_line)
// 		printf("\n");
// 	return (0);
// }
int	is_valid_n_flag(char *s)
{
	int	i = 0;

	if (!s || s[i++] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	my_echo(t_env *custom_envp, char **args)
{
	int	i;
	int	new_line;

	(void)custom_envp;
	i = 1;
	new_line = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
