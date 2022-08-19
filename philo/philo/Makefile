CC = cc

NAME = philo

CFLAGS = -Wall -Werror -Wextra
#CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

SRCS =	philo.c 			\
		philo_utils.c		\
		philo_input.c		\
		philo_timer.c		\
		philo_lifecycle.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

all : $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

debug: all
	$(CC) -lpthread $(OBJS) -o $(NAME)
#$(CC) -lpthread $(OBJS) -o $(NAME) -fsanitize=address

lldb: all
	$(CC) $(CFLAGS) -lpthread $(SRCS) -o $(NAME) -g3

re:
	make fclean
	make all

.PHONY: all clean fclean re
