/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:47:37 by alisharu          #+#    #+#             */
/*   Updated: 2025/05/21 12:51:40 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		pthread_create(&table->philo[index].thread, NULL,
			actions, &table->philo[index]);
		usleep(100);
		index++;
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
