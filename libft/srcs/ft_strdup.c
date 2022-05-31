/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:24:36 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:24:41 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = ft_calloc((ft_strlen(s1) + 1), 1);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}
