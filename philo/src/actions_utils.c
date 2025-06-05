/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:54:01 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:54:01 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *str)
{
	pthread_mutex_lock(&philo->table->program_stop_mutex);
	if (!philo->table->program_stop)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("[%ld] %d %s\n", get_time_in_ms()
			- philo->table->start_time, philo->index, str);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	pthread_mutex_unlock(&philo->table->program_stop_mutex);
}

void	*actions(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->program_stop_mutex);
		if (philo->table->program_stop)
			return (pthread_mutex_unlock(&philo->table->program_stop_mutex),
				NULL);
		pthread_mutex_unlock(&philo->table->program_stop_mutex);
		philo_eating(philo);
		print_action(philo, "is sleeping");
		philo_usleep(philo, philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
