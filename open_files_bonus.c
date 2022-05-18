#include "pipex_bonus.h"

/* open_files():
** line 10: Heredoc reads from input instead of file.
*/
void	open_files(int argc, char **argv, int *file_fd)
{
	if (is_heredoc(argv[1]))
	{
		file_fd[READ] = read_stdin(argv[2]);
		file_fd[WRITE] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		file_fd[READ] = open(argv[1], O_RDONLY);
		if (file_fd[READ] == -1)
			perror(argv[1]);
		file_fd[WRITE] = open(argv[argc - 1],
				O_WRONLY | O_CREAT, 0644);
	}
}

/* read_stdin():
** line 41~44: Receive infinite input ending with newline.
** line 45~46: When input is the same string as [limiter],
**				child process is terminated.
** line 47~48: Until terminated, continue writing to the pipe.
*/
int	read_stdin(const char *limiter)
{
	int			pipe_fd[2];
	pid_t		pid;
	const char	*line;

	pipe(pipe_fd);
	pid = fork();
	if (pid == CHILD)
	{
		close(pipe_fd[READ]);
		while (1)
		{
			write(2, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (is_limiter(line, limiter))
				exit(EXIT_SUCCESS);
			else
				write(pipe_fd[WRITE], line, ft_strlen(line));
		}
	}
	close(pipe_fd[WRITE]);
	wait(NULL);
	return (pipe_fd[READ]);
}
