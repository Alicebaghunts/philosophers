/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 15:00:15 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-21 15:00:15 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "unistd.h"

void	print_string(t_table *table, char *str, int index)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("[%ld] %d %s\n", get_time_in_ms() - table->start_time,
		index + 1, str);
	pthread_mutex_unlock(&table->print_mutex);
}

void	*check_philosopher_death(void *data)
{
	t_table	*table;
	int		index;

	table = (t_table *)data;
	while (1)
	{
		usleep(10000);
		index = 0;
		while (index < table->philo_count)
		{
			pthread_mutex_lock(&table->philo[index].last_meal_mutex);
			if (get_time_in_ms() - table->philo[index].last_meal
				> table->time_to_die)
			{
				pthread_mutex_unlock(&table->philo[index].last_meal_mutex);
				pthread_mutex_lock(&table->program_stop_mutex);
				table->program_stop = 1;
				pthread_mutex_unlock(&table->program_stop_mutex);
				print_string(table, "philo is dead", index);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philo[index].last_meal_mutex);
			index++;
		}
	}
	return (NULL);
}


void	*check_all_philosophers_full(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		pthread_mutex_lock(&table->num_eats_mutex);
		if (table->full_eats_count == table->philo_count)
		{
			pthread_mutex_lock(&table->program_stop_mutex);
			table->program_stop = 1;
			pthread_mutex_lock(&table->print_mutex);
			printf("[%ld] Dinner is over\n", get_time_in_ms()
				- table->start_time);
			pthread_mutex_unlock(&table->print_mutex);
			pthread_mutex_unlock(&table->program_stop_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
