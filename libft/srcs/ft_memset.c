/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:23:31 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:23:39 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*s2;
	size_t			i;

	s2 = s;
	i = 0;
	while (i < len)
	{
		s2[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
