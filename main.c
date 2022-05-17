#include "pipex.h"

/** Mandatory Part **/

/* This program is executed as follows:
** $> ./pipex file1 cmd1 cmd2 file2
** and it behave exactly the same as the shell command below:
** $> <file1 cmd1 | cmd2 > outfile
*/

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

/* main():
** 1) Check if they are valid arguments.
** 2) Open [file1] and [file2] and save fd to [file_fd].
** 3) Create a childlist. the number of "list nodes == [cmd]s == child processes".
** 4) The parent creates pipes and child processes while traversing the [childlist].
** 5) Each child process executes its own command and exits.
** 6) The parent process waits for every child process to terminate,
**    and then deallocates each node.
*/

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
			if (child->pid == 0)
				child_process(file_fd, pipe_fd, child);
			parent_process(file_fd, pipe_fd, child);
			child = child->next;
		}
		parent_wait_children(childlist);
	}
	else
		write(2, "Error: bad arguments\n", 22);
	return (0);
}

/* fork_process():
** The child process will write the result to a pipe(a.k.a. pipe_fd[WRITE])
** instead of displaying it to the terminal(a.k.a. fd 1).
** That way the next child process can read instead of fd 0. */
void	fork_process(int *pipe_fd, t_childlist *child)
{
	if (child->next)
		pipe(pipe_fd);
	child->pid = fork();
}

/* parent_process():
** 1) Since the child process inherits all the file descriptors,
**    it no longer need to have it right after fork().
** 2) file_fd[READ] is an exception.
**    It should be passed on to the next child process and then closed.
*/
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
