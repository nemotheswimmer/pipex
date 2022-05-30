/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:26:22 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:48:44 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_children(t_childlist *childlist)
{
	t_childlist	*child;
	t_childlist	*temp;

	child = childlist;
	while (child)
	{
		waitpid(child->pid, NULL, 0);
		temp = child->next;
		free_child(child);
		child = temp;
	}
}

void	free_child(t_childlist *child)
{
	free_twoarr(child->command);
	free(child->full_path);
	free(child);
}
