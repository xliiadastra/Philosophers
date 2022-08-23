/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_timer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichoi <yichoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:38:20 by yichoi            #+#    #+#             */
/*   Updated: 2022/08/23 20:51:41 by yichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t  get_time()
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
