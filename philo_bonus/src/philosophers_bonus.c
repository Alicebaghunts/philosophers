/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:39:31 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/02 21:48:25 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_signal(int signum)
{
	if (signum == SIGTERM)
	{
		printf("aaa\n");
		exit(0);
	}
}

void	create_philo(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		table->pid[index] = fork();
		if (table->pid[index] == 0)
		{
			signal(SIGTERM, handle_signal);
			actions(&table->philo[index]);
		}
		++index;
	}
}
