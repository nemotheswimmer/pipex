/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:21:25 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 16:41:01 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_cntnbr(int n)
{
	long long	ln;
	size_t		cnt;

	ln = n;
	if (n < 0)
		ln = -ln;
	cnt = 1;
	while (ln / 10)
	{
		ln = ln / 10;
		cnt++;
	}
	return (cnt);
}

static void	ft_putrnbr(char *s, int n, size_t cnt)
{
	long long	ln;

	ln = n;
	if (n < 0)
		ln = -ln;
	while (cnt)
	{
		s[cnt - 1] = (ln % 10) + '0';
		ln = ln / 10;
		cnt--;
	}
}

char	*ft_itoa(int n)
{
	int		neg;
	size_t	cnt;
	char	*s;

	neg = 0;
	if (n < 0)
		neg = 1;
	cnt = ft_cntnbr(n);
	s = ft_calloc((cnt + neg + 1), 1);
	if (neg)
		*s = '-';
	ft_putrnbr((s + neg), n, cnt);
	return (s);
}
