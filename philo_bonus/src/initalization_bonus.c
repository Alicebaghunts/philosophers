/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalization_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 15:14:12 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 15:14:12 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include "philo_bonus.h"

int	init_semaphore(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/secure_forks");
	sem_unlink("/fullness");
	sem_unlink("/death");
	sem_unlink("/all_stop");


	table->forks = sem_open("/forks", O_CREAT, 0644, table->philo_count);
	table->print = sem_open("/print", O_CREAT, 0644, 1);
	table->fullness = sem_open("/fullness", O_CREAT, 0644, 0);
	table->death = sem_open("/death", O_CREAT, 0644, 0);
	table->all_dead_sem = sem_open("/all_stop", O_CREAT, 0644, 1);
	table->secure_forks = sem_open("/secure_forks", O_CREAT, 0644, 1);

	if (table->forks == SEM_FAILED || table->print == SEM_FAILED
		|| table->fullness == SEM_FAILED || table->death == SEM_FAILED
		|| table->all_dead_sem == SEM_FAILED
		|| table->secure_forks == SEM_FAILED)
		return (error_handling(SEMAPHORE_INIT_ERROR), 0);
	return (1);
}

void	free_semaphores(t_table *table)
{
	int		i;
	char	*name;

	i = 0;
	while (i < table->philo_count)
	{
		sem_close(table->philo[i].t_sem);
		name = ft_itoa(i);
		sem_unlink(name);
		free(name);
		i++;
	}
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->secure_forks);
	sem_unlink("/secure_forks");
	sem_close(table->print);
	sem_unlink("/print");
	sem_close(table->all_dead_sem);
	sem_unlink("/all_dead");
	sem_close(table->fullness);
	sem_unlink("/fullness");
	sem_close(table->death);
	sem_unlink("/death");
}


void	free_table(t_table *table)
{
	if (!table)
		return ;
	free_semaphores(table);
	if (table->philo)
		free(table->philo);
	free(table);
}


int	init_philo(t_table *table)
{
	int		index;
	char	*semaphore_name;

	index = 0;
	table->philo = ft_calloc(table->philo_count, sizeof(t_philo));
	if (table->philo == NULL)
		return (error_handling(CALLOC_ERROR), 0);
	while (index < table->philo_count)
	{
		table->philo[index].index = index + 1;
		table->philo[index].eat_count = 0;
		table->philo[index].last_meal = table->start_time;
		table->philo[index].table = table;
		semaphore_name = ft_itoa(index);
		sem_unlink(semaphore_name);
		table->philo[index].last_meal_sem
			= sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, 1);
		free(semaphore_name);
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
	table->num_eats_count = 0;
	table->full_eats_count = 0;
	table->program_stop = 0;
	if (argc == 6)
		table->num_eats_count = ft_atol(argv[5]);
	if (init_semaphore(table) == 0)
		return (free_table(table), NULL);
	if (init_philo(table) == 0)
		return (free_table(table), NULL);
	table->start_time = get_time_in_ms();
	return (table);
}

