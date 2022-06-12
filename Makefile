# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 08:24:34 by yehan             #+#    #+#              #
#    Updated: 2022/06/13 07:48:14 by yehan            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #


NAME		:= pipex

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f

LIBFLAGS	:= -L./libft -lft

FTDIR		:= ./libft

SRCS	:= \
				main.c \
				open_files.c \
				get_childlist.c \
				child_process.c \
				wait_children.c \
				utils.c

SRCS_BONUS	:= \
				main_bonus.c \
				open_files_bonus.c \
				get_childlist_bonus.c \
				child_process_bonus.c \
				wait_children_bonus.c \
				utils_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

ifdef BONUS
	OBJS	= $(OBJS_BONUS)
endif

.PHONY:		all clean fclean rclean re bonus

all:		$(NAME)

clean:
			make clean --directory=$(FTDIR)
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			make fclean --directory=$(FTDIR)
			$(RM) $(NAME)

rclean:		fclean
			$(RM) infile outfile

re:			fclean all

bonus:
			make BONUS=true

$(NAME):	$(OBJS)
			make --directory=$(FTDIR)
			$(CC) $(CFLAGS) $(LIBFLAGS) $^ -o $@
