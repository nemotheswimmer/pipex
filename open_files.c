/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:25:38 by yehan             #+#    #+#             */
/*   Updated: 2022/05/31 08:25:48 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* open_files():
** The actual shell opens all files at the first point.
** line 22: The file to receive input is opened only when it exists,
** line 25: and the file to be output is opened or newly created.
*/
void	open_files(int argc, char **argv, int *file_fd)
{
	file_fd[READ] = open(argv[1], O_RDONLY);
	if (file_fd[READ] == -1)
		perror(argv[1]);
	file_fd[WRITE] = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
}
