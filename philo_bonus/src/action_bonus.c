/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicebaghunts <alicebaghunts@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:52:52 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/07 15:16:38 by alicebaghun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_fork(t_philo *philo)
{
	sem_wait(philo->table->deadlock_protect);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time_in_ms();
	sem_post(philo->last_meal_sem);
}

void	put_fork(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	sem_post(philo->table->deadlock_protect);
}

void	philo_eating(t_philo *philo)
{
	pick_fork(philo);
	print_action(philo, "eating");
	philo_usleep(philo->table->time_to_eat);
	put_fork(philo);
	if (philo->table->num_eats_count
		&& ++philo->eat_count == philo->table->num_eats_count)
		sem_post(philo->table->fullness);
}
