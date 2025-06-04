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
	sem_unlink("/all_dead_sem");
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
	if (table->pid)
		free(table->pid);
	free_semaphores(table);
	close_semaphores(table);
	if (table->philo)
		free(table->philo);
	if (table)
		free(table);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			len;
	size_t			i;

	len = size * count;
	if (len == 0)
		return (malloc(1));
	if (len / size != count)
		return (NULL);
	ptr = (unsigned char *)malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
