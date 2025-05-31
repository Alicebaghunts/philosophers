/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-31 16:15:13 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-31 16:15:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_string(t_philo *philo, char *str, int index)
{
    sem_wait(philo->table->print);
	printf("[%lld] %d %s\n", get_time_in_ms() - philo->table->start_time,
		index + 1, str);
    sem_post(philo->table->print);
}

static void kill_all_philosophers(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_count)
        kill(table->philo[i].pid, SIGKILL);
}

static int check_main_death(t_philo *philo, int index)
{
    if (get_time_in_ms() - philo->table->philo[index].last_meal
        >= philo->table->time_to_die)
    {
        sem_post(philo->table->philo[index].last_meal_sem);
        sem_wait(philo->table->stop_sem);
        philo->table->program_stop = 1;
        sem_post(philo->table->stop_sem);
        print_string(&philo->table->philo[index], "dead", index);
        kill_all_philosophers(philo->table);
        return (0);
    }
    return (1);
}

void *check_philosopher_death(void *data)
{
    t_philo *philo;
    int     index;
    
    philo = (t_philo *)data;
    while (1)
    {
        usleep(100);
        sem_wait(philo->table->stop_sem);
        if (philo->table->program_stop)
            return (sem_post(philo->table->stop_sem), NULL);
        sem_post(philo->table->stop_sem);
        index = -1;
        while (++index < philo->table->philo_count)
        {
            sem_wait(philo->table->philo[index].last_meal_sem);
            if (check_main_death(philo, index) == 0)
                return (NULL);
            sem_post(philo->table->philo[index].last_meal_sem);
        }
    }
    return (NULL);
}
