/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:37:31 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/26 18:51:11 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

# define INT_MAX 2147483647ULL

typedef struct s_sem
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*eat_checker;	
}	t_sem;

typedef struct s_arg
{
	int		die_time;
	int		n_philo;
	int		eat_time;
	int		sleep_time;
	int		must_eat;
}	t_arg;

typedef struct s_info
{
	t_arg		arg;
	t_sem		sema;
	size_t		birth_t;
	pid_t		*pid;
}	t_info;

typedef struct s_philo
{
	int 	idx;
	t_info	info;
	size_t	last_eat_t;
	int		eat_cnt;
}	t_philo;

typedef enum e_status
{
	SUCCESS,
	ERROR
}	t_status;



long long	ft_atoi(const	char	*str);
int	ft_error(void);
int	ft_fail(pid_t *pid);
int	ft_isstrdigit(char *str);
void	mutex_free(t_philo *philo);
unsigned long long	ft_atol(const char *str);
int	ft_strstr(char *str1, char *str2);
size_t  get_time();
int    smart_timer(size_t time);
int	check_input(int argc, char *argv[]);
int	parse_arg(int argc, char **argv, t_info *info);
int	init_philo(t_info *info, t_arg *arg);
void	philo_fork(t_philo philo, pid_t *pid);
void	philo_print(t_philo *philo, t_info *info, int idx, char *str);
int take_fork(t_philo *philo);
int	eating(t_philo *philo);
int	sleep_thinking(t_philo *philo);
void action(t_philo philo);
void	*monitor(void *param);
void *eat_checker(void *param);
void	sem_or_pid_free(t_philo *philo, pid_t *pid);
void	kill_dem_all(t_philo *philo, pid_t *pid);

#endif
