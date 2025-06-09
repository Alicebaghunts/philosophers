/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:52:46 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:52:46 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	actions(t_philo *philo)
{
	pthread_create(&philo->table->monitoring_thread,
		NULL, check_death_philo, philo);
	if (philo->index % 2 == 0)
		usleep(500);
	while (1)
	{
		philo_eating(philo);
		print_action(philo, "philo sleeping");
		philo_usleep(philo->table->time_to_sleep);
		print_action(philo, "philo thinking");
	}
	pthread_join(philo->table->monitoring_thread, NULL);
}

void	print_action(t_philo *philo, const char *str)
{
	sem_wait(philo->table->stop_sem);
	if (philo->table->program_stop == 1)
	{
		sem_post(philo->table->stop_sem);
		return ;
	}
	sem_post(philo->table->stop_sem);
	sem_wait(philo->table->print);
	printf("[%lld] %d %s\n", get_time_in_ms()
		- philo->table->start_time, philo->index, str);
	sem_post(philo->table->print);
}

void	one_philo_pick_fork(t_philo *philo)
{
	sem_wait(philo->table->deadlock_protect);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	usleep((philo->table->time_to_die + 1) * 1000);
	print_action(philo, "is dead");
	sem_post(philo->table->death);
	sem_post(philo->table->forks);
	sem_post(philo->table->deadlock_protect);
}
