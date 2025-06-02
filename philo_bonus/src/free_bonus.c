/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:27:18 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/02 18:21:46 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_unlink("/forks");
	sem_close(table->deadlock_protect);
	sem_unlink("/deadlock_protect");
	sem_close(table->print);
	sem_unlink("/print");
	sem_close(table->all_dead_sem);
	sem_unlink("/all_dead");
	sem_close(table->fullness);
	sem_unlink("/fullness");
	sem_close(table->stop_sem);
	sem_unlink("/stop_sem");
	sem_close(table->death);
	sem_unlink("/death");
}

void	free_semaphores(t_table *table)
{
	int		i;
	char	*name;

	i = 0;
	while (i < table->philo_count)
	{
		sem_close(table->philo[i].last_meal_sem);
		name = ft_itoa(i);
		sem_unlink(name);
		free(name);
		i++;
	}
}


void	free_table(t_table *table)
{
	if (!table)
		return ;
	free(table->pid);
	free_semaphores(table);
	if (table->philo)
		free(table->philo);
	free(table);
}