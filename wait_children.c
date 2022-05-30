/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:26:27 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:26:45 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* wait_children():
** line 26: While iterate the [childlist],
** line 28: wait every child process in the order in the list
** line 29~31: and free the node.
*/
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
