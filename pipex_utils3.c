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

void	wait_children(t_childlist *childlist)
{
	while (childlist)
	{
		waitpid(childlist->pid, NULL, 0);
		childlist = childlist->next;
	}
}
