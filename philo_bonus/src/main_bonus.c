/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 15:13:15 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 15:13:15 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_table *table)
{
	pthread_mutex_lock(&table->program_stop_mutex);
	printf("[%ld] 1 has taken a fork\n", get_time_in_ms()
		- table->start_time);
	usleep((table->time_to_die + 1) * 1000);
	printf("[%ld] 1 died\n", get_time_in_ms()
		- table->start_time);
	pthread_mutex_unlock(&table->program_stop_mutex);
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		index;

	index = 0;
	if (validation(argc, argv) == 0)
		return (0);
	table = init_table(argc, argv);
	if (table->philo_count == 1)
		return (one_philo(table), 0);
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
