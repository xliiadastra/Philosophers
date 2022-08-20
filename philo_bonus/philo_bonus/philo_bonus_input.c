#include "philo_bonus.h"

int     check_input(int argc, char *argv[])
{
        int     i;

        i = 0;
        if (!(argc == 5 || argc == 6))
                return (ERROR);
        while (++i < argc)
                if (ft_isstrdigit(argv[i]))
                        return (ERROR);
        return (SUCCESS);
}

int     parse_arg(int argc, char **argv, t_info *info)
{
        info->arg.n_philo = atoi(argv[1]);
        info->arg.die_time = atoi(argv[2]);
        info->arg.eat_time = atoi(argv[3]);
        info->arg.sleep_time = atoi(argv[4]);
        if (argc == 6)
                info->arg.must_eat = atoi(argv[5]);
        else
                info->arg.must_eat = 0;
        if (info->arg.n_philo <= 0 || info->arg.die_time <= 0 || info->arg.eat_time < 0 || info->arg.sleep_time < 0 || info->arg.must_eat < 0)
                return (ERROR);
        return (SUCCESS);
}

int init_philo(t_philo *philo, t_info *info, t_arg *arg)
{
        (*philo).last_eat_t = get_time();
        info->sema.fork = sem_open("sem_fork", O_CREAT | O_EXCL, 0644, arg->n_philo);
        if (info->sema.fork == SEM_FAILED)
        {
                sem_unlink("sem_fork");
                info->sema.fork = sem_open("sem_fork", O_CREAT | O_EXCL, 0644, arg->n_philo);
        }
        info->sema.print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
        if (info->sema.print == SEM_FAILED)
        {
                sem_unlink("sem_print");
                info->sema.print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
        }
        info->sema.eat_checker = sem_open("eat_checker", O_CREAT | O_EXCL, 0644, 0);
        if (info->sema.eat_checker == SEM_FAILED)
        {
                sem_unlink("eat_checker");
                info->sema.eat_checker = sem_open("eat_checker", O_CREAT | O_EXCL, 0644, 0);
        }
        return (SUCCESS);
}
