#include "pipex.h"

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

t_childlist	*lstlast(t_childlist *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_childlist **lst, t_childlist *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		lstlast(*lst)->next = new;
}

t_childlist *lstnew(char *argvi, char **paths)
{
	t_childlist	*new;

	new = ft_calloc(sizeof(t_childlist), 1);
	new->command = ft_split(argvi, ' ');
	new->full_path = get_full_path((new->command)[0], paths);
	return (new);
}

/* create childlist with one member(char **command) filled.
** other members are 0(blank) yet.
*/
t_childlist	*get_childlist(int argc, char **argv, char **envp)
{
	int					i;
	char				**paths;
	t_childlist			*new;
	static t_childlist	*childlist;

	paths = get_paths(envp);
	i = 2 + is_heredoc(argv[1]);
	while (i < argc - 1)
	{
		new = lstnew(argv[i], paths);
		lstadd_back(&childlist, new);
		i++;
	}
	free_twoarr(paths);
	return (childlist);
}

void	reset_stdin(int *file_fd)
{
	dup2(file_fd[READ], STDIN_FILENO);
	close(file_fd[READ]);
}

/* if this is last process to execute,
** write to the outfile we opened,
** not one a pipe(there's no pipe_fd this time).
*/
void	reset_stdout(int *file_fd, int *pipe_fd, t_childlist *childlist)
{
	if (childlist->next)
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
		exit(127);
	}
}
