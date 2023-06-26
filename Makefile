CC			=	cc -fsanitize=thread
CC			=	cc #-fsanitize=address
# CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g

INCLUDES	=	./includes
RM			=	/bin/rm -f
NAME		=	philo

SRCS		=	main.c \
				util.c \
				philo.c \
				check.c \
				actions.c \
				routine.c \
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
#  --thread-locks=yes --thread-safety=:<high> --fair-sched=yes --track-origins=yes
v:
	make re && clear && valgrind -s --tool=helgrind --history-level=approx ./philo 5 100 100 100

.PHONY: all re clean fclean m
