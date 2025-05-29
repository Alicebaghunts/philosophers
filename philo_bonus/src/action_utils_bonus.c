/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 16:41:42 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 16:41:42 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	actions(t_philo *philo)
{
	pthread_create(philo->table->death_thread, NULL, check_philo_dead, philo);
	while (1)
	{
		sem_wait(philo->last_meal_sem);
		philo->last_meal = get_time_in_ms();
		sem_post(philo->last_meal_sem)
		philo_eating(philo);
		print_action(philo, "is sleeping");
		philo_usleep(philo, philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	pthread_join(philo->table->death_thread);
}

void	print_action(t_philo *philo, const char *str)
{
	sem_wait(philo->table->print);
	printf("[%ld] %d %s\n", get_time_in_ms()
		- philo->table->start_time, philo->index, str);
	sem_post(philo->table->print);
}
