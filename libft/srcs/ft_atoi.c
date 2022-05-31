/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:18:44 by yehan             #+#    #+#             */
/*   Updated: 2021/12/18 12:10:20 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static bool	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int			neg;
	size_t		num;
	long int	cnt;

	while (ft_isspace(*str))
		str++;
	neg = 1;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	cnt = LONG_MAX;
	while ('0' <= *str && *str <= '9')
	{
		if (neg == -1 && (!cnt || num > -(size_t)LONG_MIN))
			return ((int)LONG_MIN);
		if (neg == 1 && (!cnt || num > (size_t)LONG_MAX))
			return ((int)LONG_MAX);
		num = num * 10 + (*str - '0');
		cnt = cnt / 10;
		str++;
	}
	return (neg * num);
}
