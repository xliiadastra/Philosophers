/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:26:43 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/26 18:54:05 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	info->arg.n_philo = ft_atol(argv[1]);
	info->arg.die_time = ft_atol(argv[2]);
	info->arg.eat_time = ft_atol(argv[3]);
	info->arg.sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		info->arg.must_eat = ft_atol(argv[5]);
	else
		info->arg.must_eat = 0;
	if (info->arg.n_philo <= 0 || info->arg.die_time <= 0
		|| info->arg.eat_time < 0 || info->arg.sleep_time < 0
		|| info->arg.must_eat < 0)
		return (ERROR);
	return (SUCCESS);
}

int	init_philo(t_info *info, t_arg *arg)
{
	sem_unlink("sem_fork");
	info->sema.fork = sem_open("sem_fork", O_CREAT | O_EXCL, 0644, arg->n_philo);
	if (info->sema.fork == SEM_FAILED)
		return (ERROR);
	sem_unlink("sem_print");
	info->sema.print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (info->sema.print == SEM_FAILED)
		return (ERROR);
	sem_unlink("eat_checker");
	info->sema.eat_checker = sem_open("eat_checker", O_CREAT | O_EXCL, 0644, 0);
	if (info->sema.eat_checker == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

void	sem_or_pid_free(t_philo *philo, pid_t *pid)
{
	sem_close(philo->info.sema.fork);
	sem_close(philo->info.sema.print);
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	free(pid);
	pid = NULL;
}
