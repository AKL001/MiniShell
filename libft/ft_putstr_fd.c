/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <ablabib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:52:03 by ablabib           #+#    #+#             */
/*   Updated: 2024/10/27 15:54:43 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	ssize_t	written;

	if (!s || fd < 0)
		return (1);
	written = write(fd, s, ft_strlen(s));
	if (written == -1)
		return (1);
	return (0);
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	size_t	s_len;

// 	if (!s || fd < 0)
// 		return ;
// 	s_len = ft_strlen(s);
// 	write(fd, s, s_len);
// }
