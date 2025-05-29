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

void	philo_pick_fork(t_philo *philo)
{
	sem_wait(philo->table->secure_forks);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	if (philo->table->philo_count == 1)
	{
		sem_post(philo->table->forks);
		sem_post(philo->table->secure_forks);
		usleep((philo->table->time_to_die + 2) * 1000);
		sem_post(philo->table->death);
	}
	sem_wait(philo->table->forks);
	print_state(philo, "has taken a fork");
}

