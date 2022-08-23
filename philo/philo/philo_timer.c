/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:16:20 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/23 20:10:21 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (ERROR);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	smart_timer(size_t time)
{
	size_t	start;

	start = get_time();
	if (start == ERROR)
		return (ERROR);
	while (get_time() - start < time)
		usleep(100);
	return (SUCCESS);
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
