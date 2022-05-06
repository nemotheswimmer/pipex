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

void	free_child(t_childlist **childlist)
{
	char	**str;

	str = (*childlist)->command;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(*childlist);
}

/* do 3 things:
** 1) wait child process in the order in the list,
** 1-1) close fd read by the process,
** 1-2) free the node (include char **command)
*/
void	wait_children(t_childlist **childlist)
{
	t_childlist	*curr;
	t_childlist	*temp;

	curr = *childlist;
	while (curr)
	{
		waitpid(curr->pid, NULL, 0);
		close(curr->fd_read);
		temp = curr->next;
		free_child(&curr);
		curr = temp;
	}
}
