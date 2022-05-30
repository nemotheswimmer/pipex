/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:26:02 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:26:53 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include "./libft/include/libft.h"

# define READ 0
# define WRITE 1
# define CHILD 0

typedef struct s_childlist
{
	char				**command;
	char				*full_path;
	pid_t				pid;
	struct s_childlist	*next;
}	t_childlist;

void		open_files(int argc, char **argv, int *file_fd);
t_childlist	*get_childlist(int argc, char **argv, char **envp);
char		**get_paths(char **envp);
t_childlist	*lstnew(char *argvi, char **paths);
char		*get_full_path(char *cmd, char **paths);
void		lstadd_back(t_childlist **lst, t_childlist *new);
void		fork_process(int *pipe_fd, t_childlist *child);
void		child_process(int *file_fd, int *pipe_fd, t_childlist *child);
void		dup2_needed_files(int *file_fd, int *pipe_fd, t_childlist *child);
void		close_all_files(int *file_fd, int *pipe_fd, t_childlist *child);
void		execve_command(t_childlist *child);
void		parent_process(int *file_fd, int *pipe_fd, t_childlist *child);
void		wait_children(t_childlist *childlist);
void		free_child(t_childlist *child);
void		free_twoarr(char **arr);

#endif
