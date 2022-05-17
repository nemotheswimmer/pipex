#include "pipex.h"

/* wait_children():
** line 14: While iterate the [childlist],
** line 16: wait every child process in the order in the list
** line 17~19: and free the node.
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
