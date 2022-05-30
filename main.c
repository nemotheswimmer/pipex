/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:24:05 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:48:52 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** Mandatory Part **/

/* This program is executed as follows:
** $> ./pipex file1 cmd1 cmd2 file2
** and it behave exactly the same as the shell command below:
** $> <file1 cmd1 | cmd2 > outfile
**
** If there is no argc limit, it also can support multi-pipe.
*/

int	main(int argc, char **argv, char **envp)
{
	int			file_fd[2];
	int			pipe_fd[2];
	t_childlist	*childlist;
	t_childlist	*child;

	if (argc == 5)
	{
		open_files(argc, argv, file_fd);
		childlist = get_childlist(argc, argv, envp);
		child = childlist;
		while (child)
		{
			fork_process(pipe_fd, child);
			if (child->pid == CHILD)
				child_process(file_fd, pipe_fd, child);
			parent_process(file_fd, pipe_fd, child);
			child = child->next;
		}
		wait_children(childlist);
	}
	else
		write(2, "Error: bad arguments\n", 22);
	return (0);
}

void	fork_process(int *pipe_fd, t_childlist *child)
{
	if (child->next)
		pipe(pipe_fd);
	child->pid = fork();
}

void	parent_process(int *file_fd, int *pipe_fd, t_childlist *child)
{
	close(file_fd[READ]);
	if (child->next)
	{
		file_fd[READ] = pipe_fd[READ];
		close(pipe_fd[WRITE]);
	}
	else
		close(file_fd[WRITE]);
}
