/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:44:29 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:44:33 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(int *file_fd, int *pipe_fd, t_childlist *child)
{
	dup2_needed_files(file_fd, pipe_fd, child);
	close_all_files(file_fd, pipe_fd, child);
	execve_command(child);
}

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
