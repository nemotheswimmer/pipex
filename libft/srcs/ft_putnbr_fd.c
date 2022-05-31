/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:24:01 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:24:09 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_putllong_fd(long long ln, int fd)
{
	char	c;

	if (ln < 10)
	{
		c = ln + '0';
		ft_putchar_fd(c, fd);
	}
	else
	{
		ft_putllong_fd(ln / 10, fd);
		ft_putllong_fd(ln % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	ln;

	if (fd < 0)
		return ;
	ln = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		ln = -ln;
	}
	ft_putllong_fd(ln, fd);
}
