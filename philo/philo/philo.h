/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:57:15 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/19 18:01:53 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX			2147483647ULL

typedef struct s_status
{
	int	death;
	int	n_full;
}	t_status;

typedef struct s_mutex
{
	pthread_mutex_t	print;
}	t_mutex;

typedef struct s_arg
{
	int		n_philo;
	size_t	die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat;
}	t_arg;

typedef struct s_info
{
	t_arg		arg;
	t_mutex		mutex;
	t_status	stat;
	size_t		birth_t;
}	t_info;

typedef struct s_philo
{
	int				idx;
	pthread_t		tid;
	int				cnt_eat;
	size_t			last_eat_t;
	t_info			*info;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

enum e_enum
{
	SUCCESS,
	ERROR
};

int					ft_error(void);
int					ft_fail(t_philo *philo);
int					ft_isstrdigit(char *str);
void				mutex_free(t_philo *philo);
int					ft_strstr(char *str1, char *str2);

int					check_input(int argc, char *argv[]);
int					parse_arg(int argc, char **argv, t_info *info);
int					init_info(t_philo **philo, t_info *info);
int					init_mutex(t_info *info, pthread_mutex_t **fork);
int					init_philo(t_philo **philo, t_info *info, t_arg *arg, \
		pthread_mutex_t *fork);

size_t				get_time(void);
int					smart_timer(size_t time);

void				philo_print(t_philo *philo, t_info *info, int idx, \
		char *str);
int					take_fork(t_philo *philo);
int					eating(t_philo *philo, t_arg *arg);
int					sleep_thinking(t_philo *philo, t_arg *arg);
void				*action(void *param);

void				*action(void *param);

unsigned long long	ft_atol(const char *str);

#endif
