/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:26:55 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:26:58 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	s = s + len;
	while (len)
	{
		if (*s == (char)c)
			return ((char *)s);
		else
		{
			s--;
			len--;
		}
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (0);
}
