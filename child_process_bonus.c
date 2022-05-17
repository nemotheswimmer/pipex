#include "pipex_bonus.h"

/* child_process():
** The child process has all the file descriptors(including pipe's fd)
** of it's parent process at the time of fork.
** Reset stdin to read from the previous pipe and stdout to write to the current pipe.
** The process exits right after executing the command.
*/
void	child_process(int *file_fd, int *pipe_fd, t_childlist *child)
{
	reset_stdin(file_fd);
	reset_stdout(file_fd, pipe_fd, child);
	execve_command(child);
}

void	reset_stdin(int *file_fd)
{
	dup2(file_fd[READ], STDIN_FILENO);
	close(file_fd[READ]);
}

/* reset_stdout():
** The last process has no pipe to write on.
** Instead, write to the [file2] we opened first.
*/
void	reset_stdout(int *file_fd, int *pipe_fd, t_childlist *child)
{
	if (child->next)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
	}
	else
	{
		dup2(file_fd[WRITE], STDOUT_FILENO);
		close(file_fd[WRITE]);
	}
}

/* execve_command():
** If there is an accessible path, run it. (the child process automatically exits.)
** If not, display an error message on the terminal like this:
** $> ls: command not found
*/
void	execve_command(t_childlist *lst)
{
	if (lst->full_path)
	{
		execve(lst->full_path, lst->command, NULL);
	}
	else
	{
		write(2, (lst->command)[0], ft_strlen((lst->command)[0]));
		write(2, ": command not found\n", 21);
		exit(EXIT_FAILURE);
	}
}
