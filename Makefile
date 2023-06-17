# CC			=	cc -fsanitize=address
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g

INCLUDES	=	./includes
RM			=	/bin/rm -f
NAME		=	philo

SRCS		=	main.c \
				util.c \
				philo.c \
				initialize.c \
				ft_calloc.c \
				time.c \

OBJS		=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

norm :
	@norminette -R CheckForbiddenSourceHeader $(SRCS) headers/

a:
	make re && clear

v:
	make re && clear && valgrind ./philo 5 100 100 100

.PHONY: all re clean fclean m
