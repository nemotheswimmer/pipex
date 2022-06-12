/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:47:20 by yehan             #+#    #+#             */
/*   Updated: 2022/06/13 07:47:25 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../include/libft.h"

# define BUFFER_SIZE 10000

char	*get_next_line(int fd);
char	*read_iter(char **s_save, int fd);
char	*get_line(char const *s_save);
char	*set_remains(char **s_save, size_t offset);

#endif
