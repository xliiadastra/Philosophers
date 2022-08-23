/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:52:55 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/23 21:33:21 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(void)
{
	printf("Arg: 5 or 6\n"
		"'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep'\n"
		"'[number_of_times_each_philosopher_must_eat]'\n");
	return (1);
}

int	ft_fail(t_philo *philo)
{
	printf("Error has occureed.\n");
	free(philo);
	philo = NULL;
	return (ERROR);
}

void	sem_free(t_philo *philo)
{
	sem_close(philo->info->sama->fork);
	sem_closw(philo->info->sama->print);
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	free(pid);
	pid = NULL;
}

int	ft_isstrdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ('0' > str[i] || str[i] > '9')
			return (ERROR);
	if (ft_atol(str) > INT_MAX)
		return (ERROR);
	return (SUCCESS);
}

unsigned long long	ft_atol(const char *str)
{
	int					i;
	unsigned long long	result;

	i = -1;
	result = 0;
	while (str[++i])
		result = result * 10 + str[i] - '0';
	return (result);
}

int	ft_strstr(char *str1, char *str2)
{
	int	i;

	i = -1;
	while (str1[++i])
		if (str1[i] != str2[i])
			return (0);
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	else
		return (0);
}
