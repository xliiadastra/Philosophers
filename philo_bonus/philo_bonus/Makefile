# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 21:07:58 by yichoi            #+#    #+#              #
#    Updated: 2022/08/23 21:12:24 by yichoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = philo_bonus

CFLAGS = -Wall -Werror -Wextra

SRCS = philo_bonus.c				\
	   philo_bonus_utils.c			\
	   philo_bonus_input.c			\
	   philo_bonus_timer.c			\
	   philo_bonus_lifecycle.c

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

re:
	make fclean
	make all

.PHONY: all clean fclean re
