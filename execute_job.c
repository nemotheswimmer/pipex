#include "pipex.h"

int	execute_job(int argc, char **argv, char **envp)
{
	int			file_fd[2];
	int			pipe_fd[2];
	t_childlist	*childlist;
	t_childlist	*child;

	open_files(argc, argv, file_fd);
	childlist = get_childlist(argc, argv, envp);
	child = childlist;
	while (child)
	{
		fork_process(pipe_fd, child);
		if (child->pid == 0)
			child_process(file_fd, pipe_fd, child);
		parent_process(file_fd, pipe_fd, child);
		child = child->next;
	}
	parent_wait_children(childlist);
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
