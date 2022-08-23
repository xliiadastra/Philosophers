#include "philo_bonus.h"

void *eat_checker(void *param)
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
    // sem_post(philo->info.sema.print);			// 세마포어 종료 및 할당한 자원 해제
    sem_close(philo->info.sema.eat_checker);			// 세마포어 종료 및 할당한 자원 해제
	sem_unlink("eat_checker"); 							// 세마포어 객체 해제 제거
	return (NULL);
}

void	*monitor(void *param)
{
	size_t	now_t;

	t_philo	*const philo  = (t_philo *)param;
	
	while (1)
	{
		sem_wait(philo->info.sema.print);
		now_t = get_time();
		if (now_t > philo->info.arg.die_time + philo->last_eat_t)
		{
			printf("%ld %d died\n", now_t - (*philo).info.birth_t, philo->idx + 1);
			exit(1);
		}
		sem_post(philo->info.sema.print);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int			idx;
	pid_t		*pid;
	t_philo		philo;
	pthread_t	tid_eatchecker;

	memset(&philo, 0, sizeof(t_philo));
	if (check_input(argc, argv) || parse_arg(argc, argv, &philo.info))
		return (ERROR);
	pid = malloc(sizeof(pid_t) * philo.info.arg.n_philo);
	if (init_philo(&philo, &philo.info, &philo.info.arg))
		return (ERROR);
	idx = 0;

	philo.info.birth_t = get_time();
	while (idx < philo.info.arg.n_philo)
	{
		pid[idx] = fork();
		if (pid[idx] == 0)
			action(philo);
		philo.idx = ++idx;
	}
	philo.info.pid = pid;
	if (argc == 6)
	{
		pthread_create(&tid_eatchecker, NULL, eat_checker, &philo);
		pthread_detach(tid_eatchecker);
	}
	waitpid(-1, 0, 0);
	idx = -1;
	while (++idx < philo.info.arg.n_philo)
		kill(pid[idx], SIGKILL);
	sem_free(&philo);
	free(pid);
	while (idx--)
		waitpid(-1, 0, 0);
	return (0);
}
