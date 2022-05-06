#include "pipex.h"

bool	is_limiter(char *line, char *limiter)
{
	return (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1));
}

/* set an index start from command argument(non-heredoc: 2, heredoc: 3),
** and split each string before get it(i.e. "ls" "-l" "a").
** to be used on second parameter of execve().
*/
// t_list	*get_cmdlist(int argc, char **argv)
// {
// 	int				i;
// 	t_list			*new;
// 	static t_list	*cmdlist;

// 	i = 2 + is_heredoc(argv[1]);
// 	while (i < argc - 1)
// 	{
// 		new = ft_lstnew(ft_split(argv[i], ' '));
// 		ft_lstadd_back(&cmdlist, new);
// 		i++;
// 	}
// 	return (cmdlist);
// }

t_childlist	*lstlast(t_childlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_cmd(t_childlist **lst, t_childlist *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		lstlast(*lst)->next = new;
}

t_childlist	*lstnew_cmd(char **command)
{
	t_childlist	*new;

	new = ft_calloc(sizeof(t_childlist), 1);
	new->command = command;
	return (new);
}

t_childlist	*get_childlist(int argc, char **argv)
{
	int					i;
	t_childlist			*new;
	static t_childlist	*childlist;

	i = 2 + is_heredoc(argv[1]);
	while (i < argc - 1)
	{
		new = lstnew_cmd(ft_split(argv[i], ' '));
		lstadd_back_cmd(&childlist, new);
		i++;
	}
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

void	execute_cmd(char **cmd, char **paths)
{
	char	*full_path;

	full_path = get_full_path(cmd[0], paths);
	if (full_path)
	{
		execve(full_path, cmd, NULL);
	}
	else
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found", 19);
		exit(127);
	}
}
