/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 16:53:05 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 16:53:05 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eating(t_philo *philo)
{
	pick_fork(philo);
	print_action(philo, "philo eating");
	philo_usleep(philo->table->time_to_eat);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_in_ms();
	sem_post(philo->last_meal_sem);
	put_fork(philo);
}
void	philo_sleeping(t_philo *philo)
{
	print_action(philo, "philo sleeping");
	philo_usleep(philo->table->time_to_sleep);
}

void	pick_fork(t_philo *philo)
{
	sem_wait(philo->table->deadlock_protect);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
}

void	put_fork(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	sem_post(philo->table->deadlock_protect);
}
void	one_philo_pick_fork(t_philo *philo)
{
	sem_wait(philo->table->deadlock_protect);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	usleep((philo->table->time_to_die + 1) * 1000);
	sem_post(philo->table->forks);
	sem_post(philo->table->deadlock_protect);
}

void	philo_usleep(int sleep_time)
{
	long	start;
	long	current;

	start = get_time_in_ms();
	while (1)
	{
		current = get_time_in_ms();
		if (current - start >= sleep_time)
			break ;
		usleep(100);
	}
}
void	philo_thinking(t_philo *philo)
{
	print_action(philo, "philo thinking");
}