/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:04:44 by ablabib           #+#    #+#             */
/*   Updated: 2025/04/09 12:04:45 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_read_until_newline(int fd)
{
	char	*buffer;
	char	c;
	int		i;
	int		bytes_read;

	buffer = malloc(1024 * sizeof(char));
	i = 0;
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
		bytes_read = read(fd, &c, 1);
	}
	buffer[i] = '\0';
	if (bytes_read <= 0 && i == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	get_next_line(char *delimiter, int heredoc_fd)
{
	char	*buffer;
	char	*delim;

	delim = ft_strjoin(delimiter, "\n");
	if (!delim)
		return (0);
	buffer = ft_read_until_newline(0);
	if (!buffer)
		return (free(delim), 0);
	if (ft_strncmp(buffer, delim, ft_strlen(delim)) == 0)
		return (free(delim), free(buffer), 0);
	write(heredoc_fd, buffer, ft_strlen(buffer));
	return (free(delim), free(buffer), 1);
}
