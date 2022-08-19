/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:50:21 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/19 18:07:36 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (!(argc == 5 || argc == 6))
		return (ERROR);
	while (++i < argc)
		if (ft_isstrdigit(argv[i]))
			return (ERROR);
	return (SUCCESS);
}

int	parse_arg(int argc, char **argv, t_info *info)
{
	info->arg.n_philo = (int)ft_atol(argv[1]);
	info->arg.die_time = (size_t)ft_atol(argv[2]);
	info->arg.eat_time = (int)ft_atol(argv[3]);
	info->arg.sleep_time = (int)ft_atol(argv[4]);
	if (argc == 6)
		info->arg.must_eat = (int)ft_atol(argv[5]);
	else
		info->arg.must_eat = 0;
	if (info->arg.n_philo <= 0 || info->arg.die_time <= 0
		|| info->arg.eat_time < 0 || info->arg.sleep_time < 0
		|| info->arg.must_eat < 0)
		return (ERROR);
	return (SUCCESS);
}

int	init_info(t_philo **philo, t_info *info)
{
	pthread_mutex_t	*fork;

	info->stat.death = 0;
	info->stat.n_full = 0;
	if (init_mutex(info, &fork) == ERROR)
		return (ERROR);
	if (init_philo(philo, info, &info->arg, fork) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	init_mutex(t_info *info, pthread_mutex_t **fork)
{
	int	i;

	*fork = malloc(sizeof(pthread_mutex_t) * info->arg.n_philo);
	if (!(*fork))
		return (ERROR);
	i = -1;
	while (++i < info->arg.n_philo)
		if (pthread_mutex_init(&(*fork)[i], PTHREAD_MUTEX_NORMAL))
			return (ERROR);
	if (pthread_mutex_init(&info->mutex.print, PTHREAD_MUTEX_NORMAL))
		return (ERROR);
	return (SUCCESS);
}

int	init_philo(t_philo **philo, t_info *info, t_arg *arg, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	(*philo) = malloc(sizeof(t_philo) * arg->n_philo);
	if (!(*philo))
		return (ERROR);
	while (++i < arg->n_philo)
	{
		(*philo)[i].idx = i;
		(*philo)[i].cnt_eat = 0;
		(*philo)[i].info = info;
		(*philo)[i].left = &fork[i];
		(*philo)[i].right = &fork[(i + 1) % arg->n_philo];
		(*philo)[i].last_eat_t = get_time();
	}
	i = -1;
	pthread_mutex_lock(&info->mutex.print);
	while (++i < arg->n_philo)
		if (pthread_create(&(*philo)[i].tid, NULL, action, &(*philo)[i]))
			return (ERROR);
	info->birth_t = get_time();
	pthread_mutex_unlock(&info->mutex.print);
	return (SUCCESS);
}
