/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:52:42 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/22 17:08:34 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_philo *philo)
{
	int	i;
	int	kill_;

	kill_ = 0;
	while (1)
	{
		i = -1;
		while (++i < philo->info->arg.n_philo)
		{
			pthread_mutex_lock(&philo->info->mutex.print);
			kill_ = philo->info->stat.death;
			if (get_time() - philo[i].last_eat_t > philo->info->arg.die_time)
			{
				philo->info->stat.death++;
				printf("%ld %d died\n", \
						get_time() - philo->info->birth_t, i + 1);
				pthread_mutex_unlock(&philo->info->mutex.print);
				return ;
			}
			else
				pthread_mutex_unlock(&philo->info->mutex.print);
			if (kill_)
				return ;
		}
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	t_info	info;
	t_philo	*philo;

	i = -1;
	if (check_input(argc, argv) || parse_arg(argc, argv, &info))
		return (ft_error());
	if (init_info(&philo, &info) == SUCCESS)
		monitor(philo);
	else
		return (ft_fail(philo));
	while (++i < philo->info->arg.n_philo)
		pthread_mutex_unlock(philo[i].left);
	i = -1;
	while (++i < philo->info->arg.n_philo)
		pthread_join(philo[i].tid, NULL);
	mutex_free(philo);
	free(philo);
	system("leaks philo");
	return (0);
}
