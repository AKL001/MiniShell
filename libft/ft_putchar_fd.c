/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <ablabib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:51:42 by ablabib           #+#    #+#             */
/*   Updated: 2024/10/27 15:53:15 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// open file table
int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (1);
	return (0);
}

// void	ft_putchar_fd(char c, int fd)
// {
// 	if (fd < 0)
// 		return ;
// 	write(fd, &c, 1);
// }
