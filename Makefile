
NAME		:= pipex

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f

LIBFTDIR	:= ../libft

SRCS	:= \
		main.c \
		open_files.c \
		get_childlist.c \
		child_process.c \
		parent_wait_children.c \
		utils.c

OBJS		= $(SRCS:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

clean:
			make clean --directory=$(LIBFTDIR)
			$(RM) $(OBJS)

fclean:		clean
			make fclean --directory=$(LIBFTDIR)
			$(RM) $(NAME)

re:			fclean all

bonus:

$(NAME):	$(OBJS)
			make --directory=$(LIBFTDIR)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)/libft.a -o $(NAME)
