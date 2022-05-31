/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:27:19 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 16:37:03 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	s2 = ft_calloc(n + 1, 1);
	ft_strlcpy(s2, s1, n + 1);
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (s == NULL || ft_strlen(s) <= start)
		return (ft_calloc(1, 1));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	return (ft_strndup(s + start, len));
}
