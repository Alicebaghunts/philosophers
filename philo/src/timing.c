/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:53:22 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:53:22 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_usleep(t_philo *philo, int sleep_time)
{
	long	start;
	long	current;

	start = get_time_in_ms();
	while (1)
	{
		current = get_time_in_ms();
		if (current - start >= sleep_time)
			break ;
		pthread_mutex_lock(&philo->table->program_stop_mutex);
		if (philo->table->program_stop)
		{
			pthread_mutex_unlock(&philo->table->program_stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->program_stop_mutex);
		usleep(100);
	}
}
