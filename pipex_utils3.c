#include "pipex.h"

char	*get_full_path(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!access(full_path, X_OK))
		{
			return (full_path);
		}
		else
		{
			free(full_path);
			i++;
		}
	}
	return (NULL);
}

/* 1) free char **command
** 2) free char *full_path
*/
void	free_child(t_childlist *node)
{
	free_twoarr(node->command);
	free(node->full_path);
	free(node);
}

/* do 3 things:
** 1) wait child process in the order in the list,
** 1-1) close fd read by the process,
** 1-2) free the node (include char **command)
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

void	free_twoarr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}
