# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 20:09:41 by yichoi            #+#    #+#              #
#    Updated: 2022/08/23 20:12:03 by yichoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = philo

CFLAGS = -Wall -Werror -Wextra

SRCS =	philo.c 			\
		philo_utils.c		\
		philo_input.c		\
		philo_timer.c		\
		philo_lifecycle.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

all : $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

#debug: all
#	$(CC) -lpthread $(OBJS) -o $(NAME)

#lldb: all
#	$(CC) $(CFLAGS) -lpthread $(SRCS) -o $(NAME) -g3

re:
	make fclean
	make all

.PHONY: all clean fclean re
