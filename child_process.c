/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:22:07 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:22:50 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* child_process():
** The child process has all the fd (including pipe's fd.)
** of it's parent process at the time of fork.
** line 24: Change the action of stdin and stdout by duplication.
** line 25: Close files since they are not in use or have already copied.
** line 26: The process exits right after executing the command.
*/
void	child_process(int *file_fd, int *pipe_fd, t_childlist *child)
{
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
** line 62~65: If there is an accessible path, run it.
** 				(The child process automatically exits.)
** line 66~71: If not, display an error message on the terminal like this:
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
		exit(EXIT_FAILURE);
	}
}
