
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

.PHONY:		all clean fclean re bonus

all:		$(NAME)

clean:
			make clean --directory=$(LIBFTDIR)
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			make fclean --directory=$(LIBFTDIR)
			$(RM) $(NAME)

re:			fclean all

bonus:
			make BONUS=true

$(NAME):	$(OBJS)
			make --directory=$(LIBFTDIR)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)/libft.a -o $(NAME)
