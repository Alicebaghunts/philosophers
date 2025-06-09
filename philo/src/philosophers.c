/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:53:31 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:53:31 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_table *table)
{
	int	index;

	index = -1;
	while (++index < table->philo_count)
	{
		if (pthread_create(&table->philo[index].thread, NULL,
				actions, &table->philo[index]))
			return ;
		usleep(500);
	}
}

void	joinm_philos(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		pthread_join(table->philo[index].thread, NULL);
		++index;
	}
}
