#include "pipex_bonus.h"

bool	is_valid_argc(int argc, char **argv)
{
	return ((argc >= 5 && !is_heredoc(argv[1]))
		|| (argc >= 6 && is_heredoc(argv[1])));
}

bool	is_heredoc(const char *argv1)
{
	return (!ft_strncmp(argv1, "here_doc", 9));
}

/* is_limiter():
** line 23: The program pretends that [line] has no new line,
** 			only to check if it is a [limiter].
*/
bool	is_limiter(char *line, char *limiter)
{
	size_t	n;
	size_t	i;

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
