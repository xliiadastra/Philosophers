/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:44:32 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/26 19:05:45 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*eat_checker(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	i = -1;
	while (++i < philo->info.arg.n_philo)
	{
		sem_wait(philo->info.sema.eat_checker);
		if (i + 1 == philo->info.arg.n_philo)
			break ;
		sem_post(philo->info.sema.print);
	}
	i = -1;
	while (++i < philo->info.arg.n_philo)
		kill(philo->info.pid[i], SIGKILL);
	sem_close(philo->info.sema.eat_checker);
	sem_unlink("eat_checker");
	return (NULL);
}

void	*monitor(void *param)
{
	size_t	now_t;
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->info.sema.print);
		now_t = get_time();
		if (now_t > philo->info.arg.die_time + philo->last_eat_t)
		{
			printf("%ld %d died\n", now_t - (*philo).info.birth_t,
				philo->idx + 1);
			exit(1);
		}
		sem_post(philo->info.sema.print);
	}
	return (NULL);
}

void	philo_fork(t_philo philo, pid_t *pid)
{
	int	idx;

	idx = 0;
	while (idx < philo.info.arg.n_philo)
	{
		pid[idx] = fork();
		if (pid[idx] == 0)
			action(philo);
		philo.idx = ++idx;
	}
}

void	kill_dem_all(t_philo *philo, pid_t *pid)
{
	int	idx;

	idx = -1;
	while (++idx < philo->info.arg.n_philo)
		kill(pid[idx], SIGKILL);
	sem_or_pid_free(philo, pid);
	while (idx--)
		waitpid(-1, 0, 0);
}

int	main(int argc, char *argv[])
{
	pid_t		*pid;
	t_philo		philo;
	pthread_t	tid_eatchecker;

	memset(&philo, 0, sizeof(t_philo));
	if (check_input(argc, argv) || parse_arg(argc, argv, &philo.info))
		return (ft_error());
	pid = malloc(sizeof(pid_t) * philo.info.arg.n_philo);
	if (init_philo(&philo.info, &philo.info.arg))
		return (ft_fail(pid));
	philo.info.birth_t = get_time();
	philo_fork(philo, pid);
	philo.info.pid = pid;
	if (argc == 6)
	{
		pthread_create(&tid_eatchecker, NULL, eat_checker, &philo);
		pthread_detach(tid_eatchecker);
	}
	waitpid(-1, 0, 0);
	kill_dem_all(&philo, pid);
	return (0);
}
