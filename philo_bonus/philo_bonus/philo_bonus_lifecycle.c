/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_lifecycle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:36:31 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/26 18:55:41 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_print(t_philo *philo, t_info *info, int idx, char *str)
{
	sem_wait(philo->info.sema.print);
	printf("%ld %d %s\n", get_time() - info->birth_t, idx + 1, str);
	if (strstr(str, "is eating"))
	{
		philo->last_eat_t = get_time();
		if (++(philo->eat_cnt) == info->arg.must_eat)
		{
			sem_post(info->sema.eat_checker);
			return ;
		}
	}
	sem_post(philo->info.sema.print);
}

int	take_fork(t_philo *philo)
{
	sem_wait(philo->info.sema.fork);
	philo_print(philo, &philo->info, philo->idx, "has taken a fork");
	sem_wait(philo->info.sema.fork);
	philo_print(philo, &philo->info, philo->idx, "has taken a fork");
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	philo_print(philo, &philo->info, philo->idx, "is eating");
	if (smart_timer((*philo).info.arg.eat_time))
		return (ERROR);
	return (SUCCESS);
}

int	sleep_thinking(t_philo *philo)
{
	sem_post(philo->info.sema.fork);
	sem_post(philo->info.sema.fork);
	philo_print(philo, &philo->info, philo->idx, "is sleeping");
	if (smart_timer(philo->info.arg.sleep_time))
		return (ERROR);
	philo_print(philo, &philo->info, philo->idx, "is thinking");
	return (SUCCESS);
}

void	action(t_philo philo)
{
	pthread_t	tid;

	tid = NULL;
	philo.last_eat_t = get_time();
	pthread_create(&tid, NULL, monitor, &philo);
	while (!take_fork(&philo)
		&& !eating(&philo)
		&& !sleep_thinking(&philo));
	exit(1);
}
