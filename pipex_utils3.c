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

void	lstadd_child(t_list_int **childlist, int content)
{
	t_list_int	*new;

	new = ft_lstnew_int(content);
	ft_lstadd_back_int(childlist, new);
}

int	wait_children(t_list_int *childlist)
{
	int	status;

	while (childlist)
	{
		waitpid(childlist->content, &status, 0);
		childlist = childlist->next;
	}
	return (status);
}