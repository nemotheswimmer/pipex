#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> //open()
# include <unistd.h> // pipe(), dup2(), access(), execve(), fork()
# include <sys/wait.h> //waitpid()
# include <stdbool.h>
# include "../libft/libft.h"

# define READ 0
# define WRITE 1

int		execute_job(int argc, char **argv, char **paths);
bool	is_valid_argc(int argc, char **argv);
bool	is_heredoc(const char *argv1);
char	**get_paths(char **envp);
void	open_files(int argc, char **argv, int *file_fd);
int		get_stdin_newfd(char *limiter);
bool	is_limiter(char *line, char *limiter);
t_list	*get_cmdlist(int argc, char **argv);
void	reset_stdin(int *file_fd);
void	reset_stdout(int *file_fd, int *pipe_fd, t_list *cmdlist);
void	execute_cmd(char **cmd, char **paths);
char	*get_full_path(char *cmd, char **paths);
void	lstadd_child(t_list_int **childlist, int content);
int		wait_children(t_list_int *childlist);

#endif