/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utile_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:10:36 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/18 10:32:44 by ael-aiss         ###   ########.fr       */
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

// int	is_quoted_and_strip(char **str)
// {
// 	size_t	len;
// 	char	*original;
// 	char	*new_str;
// 	int		quoted;

// 	quoted = 0;
// 	original = *str;
// 	len = ft_strlen(original);
// 	if (len >= 2 && ((original[0] == '\'' && original[len - 1] == '\'')
// 			|| (original[0] == '"' && original[len - 1] == '"')))
// 	{
// 		new_str = ft_strndup(original + 1, len - 2);
// 		free(*str);
// 		*str = new_str;
// 		return (1);
// 	}
// 	if (len >= 2 && ((original[0] == '\'' && original[1] == '\'')
// 			|| (original[0] == '"' && original[1] == '"')))
// 	{
// 		new_str = ft_strdup(original + 2);
// 		free(*str);
// 		*str = new_str;
// 		return (1);
// 	}
// 	if (len >= 2 && ((original[len - 2] == '\'' && original[len - 1] == '\'')
// 			|| (original[len - 2] == '"' && original[len - 1] == '"')))
// 	{
// 		new_str = ft_strndup(original, len - 2);
// 		free(*str);
// 		*str = new_str;
// 		return (1);
// 	}
// 	return (0);
// }
static int	is_enclosed_by_quotes(char *str, size_t len, char quote)
{
	return (len >= 2 && str[0] == quote && str[len - 1] == quote);
}

static int	process_and_replace(char **str, size_t start, size_t new_len)
{
	char	*new_str;
	char	*original;

	original = *str;
	new_str = ft_strndup(original + start, new_len);
	free(*str);
	*str = new_str;
	return (1);
}

int	is_quoted_and_strip(char **str)
{
	size_t	len;
	char	*original;

	original = *str;
	len = ft_strlen(original);
	if (is_enclosed_by_quotes(original, len, '\'')
		|| is_enclosed_by_quotes(original, len, '"'))
		return (process_and_replace(str, 1, len - 2));
	if ((len >= 2 && original[0] == '\'' && original[1] == '\'') || (len >= 2
			&& original[0] == '"' && original[1] == '"'))
		return (process_and_replace(str, 2, len - 2));
	if ((len >= 2 && original[len - 2] == '\'' && original[len - 1] == '\'')
		|| (len >= 2 && original[len - 2] == '"' && original[len - 1] == '"'))
		return (process_and_replace(str, 0, len - 2));
	return (0);
}

void	remply_redir(t_redir **redir, char *filename, t_redir_type type)
{
	char	*fname_copy;

	fname_copy = ft_strdup(filename);
	if (!fname_copy)
		return ;
	(*redir)->quoted = is_quoted_and_strip(&fname_copy);
	(*redir)->type = type;
	(*redir)->filename = ft_strdup(fname_copy);
	free(fname_copy);
}
