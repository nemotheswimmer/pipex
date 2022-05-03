#include "pipex.h"

bool	is_valid_argc(int argc, char **argv)
{
	return((argc >= 5 && !is_heredoc(argv[1]))
		|| (argc >= 6 && is_heredoc(argv[1])));
}

bool	is_heredoc(const char *argv1)
{
	return (!ft_strncmp(argv1, "here_doc", 9));
}

char	**get_paths(char **envp)
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
		else
			i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
		i++;
	}
	return (paths);
}

void	open_files(int argc, char **argv, int *file_fd)
{
	if (is_heredoc(argv[1]))
	{
		file_fd[READ] = get_stdin_newfd(argv[2]);
		file_fd[WRITE] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		file_fd[READ] = open(argv[1], O_RDONLY);
		if (file_fd[READ] == -1)
		{
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": no such file or directory", 27);
		}
		file_fd[WRITE] = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	}
}

int	get_stdin_newfd(char *limiter)
{
	int		pipe_fd[2];
	char	*line;
	int		pid;
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[READ]);
		while (1)
		{
			write(2, "heredoc> ", 9);
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
		wait(&status);
		return (pipe_fd[READ]);
	}
}
