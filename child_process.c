/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:22:07 by yehan             #+#    #+#             */
/*   Updated: 2022/06/13 08:07:15 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* child_process():
** The child process has all the fd (including pipe's fd.)
** of it's parent process at the time of fork.
** 1: Change the action of stdin and stdout by duplication.
** 2: Close files since they are not in use or have already copied.
** 3: The process exits right after executing the command.
*/
void	child_process(int *file_fd, int *pipe_fd, t_childlist *child)
{
	if (file_fd[READ] == -1)
		exit(EXIT_FAILURE);
	dup2_needed_files(file_fd, pipe_fd, child);
	close_all_files(file_fd, pipe_fd, child);
	execve_command(child);
}

/* dup2_needed_files():
** line 38~39: The last process has no pipe to write on.
**  			Instead, write to the [file2] we opened first.
*/
void	dup2_needed_files(int *file_fd, int *pipe_fd, t_childlist *child)
{
	dup2(file_fd[READ], STDIN_FILENO);
	if (child->next)
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
	else
		dup2(file_fd[WRITE], STDOUT_FILENO);
}

void	close_all_files(int *file_fd, int *pipe_fd, t_childlist *child)
{
	close(file_fd[READ]);
	close(file_fd[WRITE]);
	if (child->next)
	{
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
	}
}

/* execve_command():
** 1: If there is an accessible path, run it.
** 				(The child process automatically exits.)
** 2: If not, display an error message on the terminal like this:
** 				$> ls: command not found
*/
void	execve_command(t_childlist *child)
{
	if (child->full_path)
	{
		execve(child->full_path, child->command, NULL);
	}
	else
	{
		write(2, (child->command)[0], ft_strlen((child->command)[0]));
		write(2, ": command not found\n", 21);
	}
	exit(EXIT_FAILURE);
}
