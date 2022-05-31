/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:23:21 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:23:29 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	if (dst == NULL && src == NULL)
	{
		return (dst);
	}
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*((char *)dst + i) = *((const char *)src + i);
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			*((char *)dst + len - i - 1) = *((const char *)src + len - i - 1);
			i++;
		}
	}
	return (dst);
}
