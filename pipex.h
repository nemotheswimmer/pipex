#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> //open()
# include <unistd.h> // pipe(), dup2(), access(), execve(), fork()
# include <sys/wait.h> //waitpid()
# include <stdbool.h>
# include <sys/errno.h> //errno
# include <string.h> //strerror()
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define READ 0
# define WRITE 1

extern int errno;

typedef struct s_childlist
{
	char				**command;
	char				*full_path;
	int					pid;
	struct s_childlist	*next;
}	t_childlist;

int			execute_job(int argc, char **argv, char **paths);
void		open_files(int argc, char **argv, int *file_fd);
int			get_stdin_newfd(char *limiter);
t_childlist	*get_childlist(int argc, char **argv, char **envp);
char		**get_paths(char **envp);
t_childlist *lstnew(char *argvi, char **paths);
char		*get_full_path(char *cmd, char **paths);
void		lstadd_back(t_childlist **lst, t_childlist *new);
void		fork_process(int *pipe_fd, t_childlist *child);
void		child_process(int *file_fd, int *pipe_fd, t_childlist *child);
void		reset_stdin(int *file_fd);
void		reset_stdout(int *file_fd, int *pipe_fd, t_childlist *child);
void		execve_command(t_childlist *lst);
void		parent_process(int *file_fd, int *pipe_fd, t_childlist *child);
void		parent_wait_children(t_childlist *childlist);
void		free_child(t_childlist *child);
bool		is_valid_argc(int argc, char **argv);
bool		is_heredoc(const char *argv1);
bool		is_limiter(char *line, char *limiter);
void		free_twoarr(char **arr);

#endif
