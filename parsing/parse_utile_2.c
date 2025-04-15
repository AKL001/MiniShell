/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utile_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:10:36 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/14 19:14:26 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_quoted_and_strip(char **str)
{
	size_t	len;
	char	*original;
	char	*new_str;
	int	quoted = 0;

	original = *str;
	len = ft_strlen(original);
	if (len >= 2 && ((original[0] == '\'' && original[len - 1] == '\'')
			|| (original[0] == '"' && original[len - 1] == '"')))
	{
		new_str = ft_strndup(original + 1, len - 2);
		free(*str);
		*str = new_str;
		return (1);
	}
	if (len >= 2 && ((original[0] == '\'' && original[1] == '\'')
			|| (original[0] == '"' && original[1] == '"')))
	{
		new_str = ft_strdup(original + 2);
		free(*str);
		*str = new_str;
		return (1);
	}
	if (len >= 2 && ((original[len - 2] == '\'' && original[len - 1] == '\'')
			|| (original[len - 2] == '"' && original[len - 1] == '"')))
	{
		new_str = ft_strndup(original, len - 2);
		free(*str);
		*str = new_str;
		return (1);
	}
	return (0);
}

void	remply_redir(t_redir **redir, char *filename, t_redir_type type,
		t_command *cmd)
{
	char	*expanded;
	char	*fname_copy;

	expanded = NULL;
	fname_copy = ft_strdup(filename);
	if (!fname_copy)
		return ;
	(*redir)->quoted = is_quoted_and_strip(&fname_copy);
	(*redir)->type = type;
	if (!(*redir)->quoted)
		expanded = expand_string(fname_copy, cmd->env);
	if (expanded)
		(*redir)->filename = expanded;
	else
		(*redir)->filename = ft_strdup(fname_copy);
	free(fname_copy);
}
