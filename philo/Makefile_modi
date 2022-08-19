# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 15:18:40 by yichoi            #+#    #+#              #
#    Updated: 2022/08/03 18:30:55 by yichoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

BNS_NAME	= ./philo_bonus/philo_bonus

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm
RMFLAGS		= -f
  
INCLUDES	= ./philo.h 				\
			  ./philo_bonus.h

SRCS		=	philo.c

SRCS_BN		=	./philo_bonus/philo_bonus.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BN:.c=.o)

ifdef WITH_BONUS
	A_OBJS = $(OBJS_BONUS)
	NAME = $(BNS_NAME)
else
	A_OBJS = $(OBJS)
endif

.PHONY : all
all : $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ -I./

$(NAME) : $(A_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
	$(RM) $(RMFLAGS) $(OBJS) $(OBJS_BONUS)

.PHONY : fclean
fclean : clean
	$(RM) $(RMFLAGS) $(NAME) $(BNS_NAME)

.PHONY : re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY : bonus
bonus :
	$(MAKE) WITH_BONUS=1 all
