/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:53:27 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:53:27 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_string(t_table *table, char *str, int index)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("[%ld] %d %s\n", get_time_in_ms() - table->start_time,
		index + 1, str);
	pthread_mutex_unlock(&table->print_mutex);
}

static void	stop_program_action(t_table *table)
{
	pthread_mutex_lock(&table->program_stop_mutex);
	table->program_stop = 1;
	pthread_mutex_unlock(&table->program_stop_mutex);
}

void	*check_philosopher_death(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&table->program_stop_mutex);
		if (table->program_stop)
			return (pthread_mutex_unlock(&table->program_stop_mutex), NULL);
		pthread_mutex_unlock(&table->program_stop_mutex);
		table->idx = -1;
		while (++table->idx < table->philo_count)
		{
			pthread_mutex_lock(&table->philo[table->idx].last_meal_mutex);
			if (get_time_in_ms() - table->philo[table->idx].last_meal
				>= table->time_to_die)
			{
				pthread_mutex_unlock(&table->philo[table->idx].last_meal_mutex);
				stop_program_action(table);
				return (print_string(table, "dead", table->idx), NULL);
			}
			pthread_mutex_unlock(&table->philo[table->idx].last_meal_mutex);
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
		usleep(100);
		pthread_mutex_lock(&table->program_stop_mutex);
		if (table->program_stop)
			return (pthread_mutex_unlock(&table->program_stop_mutex), NULL);
		pthread_mutex_unlock(&table->program_stop_mutex);
		pthread_mutex_lock(&table->num_eats_mutex);
		if (table->full_eats_count == table->philo_count)
		{
			pthread_mutex_unlock(&table->num_eats_mutex);
			stop_program_action(table);
			pthread_mutex_lock(&table->print_mutex);
			printf("[%ld] Dinner is over\n",
				get_time_in_ms() - table->start_time);
			return (pthread_mutex_unlock(&table->print_mutex), NULL);
		}
		else
			pthread_mutex_unlock(&table->num_eats_mutex);
	}
	return (NULL);
}
