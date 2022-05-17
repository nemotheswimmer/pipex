#include "pipex_bonus.h"

/** Bonus Part **/

/* This program is executed as follows:
** ./pipex file1 cmd1 cmd2 file2
** and it behave exactly the same as the shell command below:
** $> <file1 cmd1 | cmd2 > outfile
**
** This program can handle multiple pipes:
** $> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
**
** and support « and » when the first parameter is "here_doc".
** This:
** $> ./pipex here_doc LIMITER cmd cmd1 file
** Behave like:
** $> cmd << LIMITER | cmd1 >> file
*/

/* You can found detailed comments in non _bonus files. */

int	main(int argc, char **argv, char **envp)
{
	int			file_fd[2];
	int			pipe_fd[2];
	t_childlist	*childlist;
	t_childlist	*child;

	if (is_valid_argc(argc, argv))
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
