/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:53:49 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:53:49 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_table *table)
{
	int	index;

	if (!table->philo)
		return ;
	index = 0;
	while (index < table->philo_count)
		pthread_mutex_destroy(&table->philo[index++].last_meal_mutex);
	free(table->philo);
}

void	free_table(t_table *table)
{
	int	index;

	if (table == NULL)
		return ;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->num_eats_mutex);
	pthread_mutex_destroy(&table->start_time_mutex);
	pthread_mutex_destroy(&table->program_stop_mutex);
	if (table->forks)
	{
		index = 0;
		while (index < table->philo_count)
			pthread_mutex_destroy(&table->forks[index++]);
		free(table->forks);
		table->forks = NULL;
	}
	index = 0;
	if (table->philo)
	{
		free(table->forks);
		table->forks = NULL;
	}
	free_philo(table);
	free(table);
}
