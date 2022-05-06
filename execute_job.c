#include "pipex.h"

int		execute_job(int argc, char **argv, char **paths)
{
	int			pid;
	int			file_fd[2];
	int			pipe_fd[2];
	t_childlist	*childlist;
	t_childlist	*curr;

	open_files(argc, argv, file_fd);
	childlist = get_childlist(argc, argv);
	curr = childlist;
	while (curr)
	{
		if (curr->next)
			pipe(pipe_fd);
		curr->pid = fork();
		if (!(curr->pid))
		{
			reset_stdin(file_fd);
			reset_stdout(file_fd, pipe_fd, curr);
			execute_cmd(curr->command, paths);
		}
		if (curr->next)
		{
		close(pipe_fd[WRITE]);
		file_fd[READ] = pipe_fd[READ];
		}
		curr->fd_read = file_fd[READ];
		curr = curr->next;
	}
	wait_children(childlist);
	return (0);
}
