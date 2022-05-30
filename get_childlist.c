/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_childlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:23:05 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:23:50 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* get_childlist():
** Returns a [childlist] filled with 2 members: [command], [full_path].
** ([pid] is initialized to 0.)
** [command] and [full_path] will be used in execve(),
** [pid] will be used in waitpid().
*/
t_childlist	*get_childlist(int argc, char **argv, char **envp)
{
	size_t				i;
	char				**paths;
	t_childlist			*child;
	static t_childlist	*childlist;

	paths = get_paths(envp);
	i = 2;
	while (i < (size_t)(argc - 1))
	{
		child = lstnew(argv[i], paths);
		lstadd_back(&childlist, child);
		i++;
	}
	free_twoarr(paths);
	return (childlist);
}

/* get_paths():
** The envp array store the environment variables.
** line 54~61: Get "PATHS enviroment variables" from [envp].
** line 62: Split it with delimeiter ':'.
** line 63~70: Add a slash(/) to each string.
** result like this:
** {"/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/sbin/", "/sbin/"}
*/
char	**get_paths(char **envp)
{
	size_t	i;
	char	*temp;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
		else
			i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
		i++;
	}
	return (paths);
}

/* lstnew():
** Create a new node filled with 2 members.
** like this:
** new->command : {"ls", "-l", "-a"}
** new->full_path : {"/bin/ls"}
*/
t_childlist	*lstnew(char *argvi, char **paths)
{
	t_childlist	*new;

	new = ft_calloc(sizeof(t_childlist), 1);
	new->command = ft_split(argvi, ' ');
	new->full_path = get_full_path((new->command)[0], paths);
	return (new);
}

/* get_full_path():
** line 101: Iterate through the [paths] array,
**  		until it finds an accessible path.
** line 103: Make a [full_path] temporarily.
** line 104: Check if it is an accessible path or not.
*/
char	*get_full_path(char *cmd, char **paths)
{
	size_t	i;
	char	*full_path;

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

void	lstadd_back(t_childlist **lst, t_childlist *new)
{
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
	}
}
