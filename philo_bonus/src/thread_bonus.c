/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:15:13 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/02 17:20:01 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_threads(t_table *table)
{
	pthread_create(&table->death_thread, NULL, death_monitor, table);
	if (table->num_eats_count > 0)
		pthread_create(&table->fullness_thread, NULL, fullness_philos, table);

	pthread_join(table->death_thread, NULL);
	if (table->num_eats_count > 0)
		pthread_join(table->fullness_thread, NULL);
}

void	*death_monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	sem_wait(table->death);
	i = -1;
	while (++i < table->philo_count)
		kill(table->pid[i], SIGKILL);
	sem_wait(table->all_dead_sem);
	table->all_dead = 1;
	sem_post(table->all_dead_sem);
	if (table->full_eats_count > 0)
		sem_post(table->fullness);
	return (NULL);
}

void	*check_death_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(1000);
		sem_wait(philo->last_meal_sem);
		if (get_time_in_ms() - philo->last_meal
			>= philo->table->time_to_die)
		{
			sem_post(philo->last_meal_sem);
			print_action(philo, "is dead");
			sem_post(philo->table->death);
			return (NULL);
		}
		sem_post(philo->last_meal_sem);
	}
	return (NULL);
}

void	*fullness_philos(void *data)
{
	t_table	*table;
	int		count;

	table = (t_table *)data;
	count = 0;
	while (1)
	{
		sem_wait(table->fullness);
		sem_wait(table->all_dead_sem);
		if (table->all_dead)
			return (sem_post(table->all_dead_sem), NULL);
		sem_post(table->all_dead_sem);
		if (++count == table->philo_count)
		{
			sem_wait(table->print);
			printf("[%lld] Dinner is over\n",
				get_time_in_ms() - table->start_time);
			sem_post(table->print);
			sem_post(table->death);
			return (NULL);
		}
	}
	return (NULL);
}


