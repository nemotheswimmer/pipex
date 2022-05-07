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

/* single line comes with newline,
** and we have to pretend it doesn't have new line.
** still we have to put the content with newline to file.
*/
bool	is_limiter(char *line, char *limiter)
{
	int	n;
	int	i;

	n = ft_strlen(line) - 1;
	i = 0;
	while (i < n)
	{
		if (line[i] != limiter[i])
			return (false);
		else
			i++;
	}
	if (limiter[i])
		return (false);
	return (true);
}

void	free_twoarr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}
