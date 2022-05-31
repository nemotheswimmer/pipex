/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:26:50 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:26:53 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	while (len && *haystack)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && i < len)
			{
				if (haystack[i] == needle[i])
					i++;
				else
					break ;
			}
			if (!needle[i])
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
