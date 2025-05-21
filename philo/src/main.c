/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:10 by miaghabe          #+#    #+#             */
/*   Updated: 2025/05/21 14:14:38 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		index;

	index = 0;
	if (validation(argc, argv) == 0)
		return (0);
	table = init_table(argc, argv);
	table->start_time = get_time_in_ms();
	create_philos(table);
	pthread_create(&table->thread_die, NULL, check_philosopher_death, table);
	if (argc == 6)
		pthread_create(&table->thread_fullness, NULL,
			check_all_philosophers_full, table);
	while (index < table->philo_count)
		pthread_join(table->philo[index++].thread, NULL);
	pthread_join(table->thread_die, NULL);
	if (argc == 6)
		pthread_join(table->thread_fullness, NULL);
	free_table(table);
	return (0);
}

