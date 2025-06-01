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
	pthread_create(&philo->table->monitoring_thread,
			NULL, check_death_philo, philo);
	while (1)
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		sem_wait(philo->table->stop_sem);
		if (philo->table->program_stop)
		{
			sem_post(philo->table->stop_sem);
			break;
		}
		sem_post(philo->table->stop_sem);
	}
	pthread_join(philo->table->monitoring_thread, NULL);
}

void	print_action(t_philo *philo, const char *str)
{
	sem_wait(philo->table->print);
	printf("[%lld] %d %s\n", get_time_in_ms()
		- philo->table->start_time, philo->index, str);
	sem_post(philo->table->print);
}
