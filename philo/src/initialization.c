/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:42:54 by miaghabe          #+#    #+#             */
/*   Updated: 2025/05/21 02:03:16 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_table *table)
{
	int	index;

	index = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->num_eats_mutex, NULL);
	pthread_mutex_init(&table->start_time_mutex, NULL);
	pthread_mutex_init(&table->program_stop_mutex, NULL);
	table->forks = ft_calloc(table->philo_count, sizeof(pthread_mutex_t));
	if (table->forks == NULL)
		return (error_handling(CALLOC_ERROR), 0);
	while (index < table->philo_count)
		pthread_mutex_init(&table->forks[index++], NULL);
	return (1);
}

int	init_philo(t_table *table)
{
	int	index;

	index = 0;
	table->philo = ft_calloc(table->philo_count, sizeof(t_philo));
	if (table->philo == NULL)
		return (error_handling(CALLOC_ERROR), 0);
	while (index < table->philo_count)
	{
		table->philo[index].index = index + 1;
		table->philo[index].eat_count = 0;
		table->philo[index].last_meal = get_time_in_ms();
		table->philo[index].left_fork = &table->forks[index];
		table->philo[index].right_fork = &table->forks[(index + 1)
			% table->philo_count];
		pthread_mutex_init(&table->philo[index].last_meal_mutex, NULL);
		table->philo[index].table = table;
		index++;
	}
	return (1);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (table == NULL)
		return (error_handling(CALLOC_ERROR), NULL);
	table->philo_count = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->num_eats = 0;
	table->full_eats_count = 0;
	table->idx = 0;
	if (argc == 6)
		table->num_eats = ft_atol(argv[5]);
	table->program_stop = 0;
	if (init_mutexes(table) == 0)
		free_table(table);
	if (init_philo(table) == 0)
		free_table(table);
	table->start_time = get_time_in_ms();
	return (table);
}
