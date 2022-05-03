#include "pipex.h"

int		execute_job(int argc, char **argv, char **paths)
{
	int					pid;
	int					file_fd[2];
	int					pipe_fd[2];
	static t_list		*cmdlist;
	static t_list_int	*childlist;

	open_files(argc, argv, file_fd);
	cmdlist = get_cmdlist(argc, argv);
	while (cmdlist)
	{
		if (cmdlist->next)
		pipe(pipe_fd);
		pid = fork();
		if (!pid)
		{
			reset_stdin(file_fd);
			reset_stdout(file_fd, pipe_fd, cmdlist);
			execute_cmd(cmdlist->content, paths);
		}
		close(pipe_fd[WRITE]);
		file_fd[READ] = pipe_fd[READ];
		cmdlist = cmdlist->next;
		lstadd_child(&childlist, pid);
	}
	return (wait_children(childlist));
}
