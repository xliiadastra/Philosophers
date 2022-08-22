/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:52:55 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/22 17:08:23 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(void)
{
	printf("Arg: 5 or 6\n"
		"'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep'\n"
		"'[number_of_times_each_philosopher_must_eat]'\n");
	return (1);
}

int	ft_fail(t_philo *philo)
{
	philo->info->stat.death++;
	printf("Error has occureed.\n");
	free(philo);
	philo = NULL;
	return (ERROR);
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

void	mutex_free(t_philo *philo)
{
	int	i;

	i = -1;
	free(philo[0].left);
	while (++i < philo->info->arg.n_philo)
		pthread_mutex_destroy(philo[i].left);
	pthread_mutex_destroy(&philo->info->mutex.print);
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
