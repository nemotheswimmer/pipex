/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:20:01 by yehan             #+#    #+#             */
/*   Updated: 2021/12/17 09:20:04 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_isupper(int c)
{
	return (0101 <= c && c <= 0132);
}

static int	ft_islower(int c)
{
	return (0141 <= c && c <= 0172);
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
