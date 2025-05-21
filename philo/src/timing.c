/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:38:16 by alisharu          #+#    #+#             */
/*   Updated: 2025/05/21 14:14:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_table *table, int index)
{
	pthread_mutex_lock(&table->philo[index].last_meal_mutex);
	if (get_time_in_ms() - table->philo[index].last_meal > table->time_to_die)
	{
		pthread_mutex_unlock(&table->philo[index].last_meal_mutex);
		pthread_mutex_lock(&table->program_stop_mutex);
		table->program_stop = 1;
		pthread_mutex_unlock(&table->program_stop_mutex);
		pthread_mutex_lock(&table->print_mutex);
		printf("[%ld] %d philo is dead", get_time_in_ms() - table->start_time,
			index + 1);
		pthread_mutex_unlock(&table->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->philo[index].last_meal_mutex);
	return (0);
}

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
