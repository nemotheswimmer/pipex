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
