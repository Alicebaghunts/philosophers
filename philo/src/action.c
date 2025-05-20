/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:10:00 by alisharu          #+#    #+#             */
/*   Updated: 2025/05/20 18:46:23 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *str)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->program_stop);
	if (!philo->table->program_stop)
	{
		pthread_mutex_unlock(&philo->table->program_stop_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("[%lld] %d %s\n", get_time_in_ms()
			- philo->table->start_time, philo->index, str);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->table->program_stop_mutex);
}

void	pick_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

void	put_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eat(t_philo *philo)
{
	pick_fork(philo);
	print_action(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->table->num_eats_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->num_eats_mutex);
	put_fork(philo);
}

void	sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}
