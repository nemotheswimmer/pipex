#include "pipex.h"

int		execute_job(int argc, char **argv, char **envp)
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
		if (child->next)
			pipe(pipe_fd);
		child->pid = fork();
		if (!(child->pid))
		{
			reset_stdin(file_fd);
			reset_stdout(file_fd, pipe_fd, child);
			execve_command(child);
		}
		close(file_fd[READ]);
		if (child->next)
		{
			file_fd[READ] = pipe_fd[READ];
			close(pipe_fd[WRITE]);
		}
		else
			close(file_fd[WRITE]);
		child = child->next;
	}
	wait_children(childlist);
	return (0);
}
