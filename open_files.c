#include "pipex.h"

void	open_files(int argc, char **argv, int *file_fd)
{
	if (is_heredoc(argv[1]))
	{
		file_fd[READ] = get_stdin_newfd(argv[2]);
		file_fd[WRITE] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		file_fd[READ] = open(argv[1], O_RDONLY, 0444);
		if (file_fd[READ] == -1)
		{
			perror(argv[1]);
		}
		file_fd[WRITE] = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	}
}

int	get_stdin_newfd(char *limiter)
{
	int		pipe_fd[2];
	int		pid;
	char	*line;

	pipe(pipe_fd);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[READ]);
		while (1)
		{
			write(2, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (is_limiter(line, limiter))
				exit(0);
			else
				write(pipe_fd[WRITE], line, ft_strlen(line));
		}
	}
	else
	{
		close(pipe_fd[WRITE]);
		wait(NULL);
		return (pipe_fd[READ]);
	}
}
