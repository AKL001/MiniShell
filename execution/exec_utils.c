#include "../includes/header.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**arr;
	int		count;
	int		i;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		arr[i++] = ft_strjoin_three(current->key, "=", current->value);
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);

}
char	*get_env_value(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

int	error_message(char *msg, int status)
{
	perror(msg);
	g_vars.g_exit_status = status;
	return (-1);
}

char	**args_to_array(t_args *args)
{
	t_args	*current;
	char	**arr;
	int		count;
	int		i;

	count = 0;
	current = args;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	current = args;
	while (current)
	{
		arr[i++] = ft_strdup(current->value);
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}
