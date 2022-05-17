#include "pipex_bonus.h"

/* parent_wait_children():
** 1) While iterate the [childlist],
** 2) wait every child process in the order in the list
** 3) and free the node.
*/
void	parent_wait_children(t_childlist *childlist)
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
