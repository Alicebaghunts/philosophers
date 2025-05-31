/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 16:39:31 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 16:39:31 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    create_philo(t_table *table)
{
    int index;

    index = 0;
    while (index < table->philo_count)
    {
        table->pid[index] = fork();
        if (table->pid[index] == 0)
            actions(&table->philo[index]);
        ++index;
    }
}
