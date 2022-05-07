#include "pipex.h"

/* do 3 things:
** 1) wait child process in the order in the list,
** 1-1) close fd read by the process,
** 1-2) free the node (include char **command)
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

/* 1) free char **command
** 2) free char *full_path
*/
void	free_child(t_childlist *child)
{
	free_twoarr(child->command);
	free(child->full_path);
	free(child);
}
