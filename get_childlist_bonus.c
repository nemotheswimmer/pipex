/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_childlist_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:22:59 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:48:55 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_childlist	*get_childlist(int argc, char **argv, char **envp)
{
	size_t				i;
	char				**paths;
	t_childlist			*child;
	static t_childlist	*childlist;

	paths = get_paths(envp);
	i = 2 + is_heredoc(argv[1]);
	while (i < (size_t)(argc - 1))
	{
		child = lstnew(argv[i], paths);
		lstadd_back(&childlist, child);
		i++;
	}
	free_twoarr(paths);
	return (childlist);
}

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

t_childlist	*lstnew(char *argvi, char **paths)
{
	t_childlist	*new;

	new = ft_calloc(sizeof(t_childlist), 1);
	new->command = ft_split(argvi, ' ');
	new->full_path = get_full_path((new->command)[0], paths);
	return (new);
}

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
