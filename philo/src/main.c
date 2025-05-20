/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:10 by miaghabe          #+#    #+#             */
/*   Updated: 2025/05/21 01:41:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*actions(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->program_stop_mutex);
		if (philo->table->program_stop)
			return (pthread_mutex_unlock(&philo->table->program_stop_mutex),
				NULL);
		pthread_mutex_unlock(&philo->table->program_stop_mutex);
		philo_eating(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	create_threads(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		pthread_create(&table->philo[index].thread, NULL,
			actions, &table->philo[index]);

		index++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		index;

	index = 0;
	if (validation(argc, argv) == 0)
		return (0);
	table = init_table(argc, argv);
	create_threads(table);
	while (index < table->philo_count)
		pthread_join(table->philo[index++].thread, NULL);
	free_table(table);
	return (0);
}
