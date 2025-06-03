/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:13:15 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/02 21:53:36 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (validation(argc, argv) == 0)
		return (0);
	table = init_table(argc, argv);
	if (table->philo_count == 1)
		return (one_philo_pick_fork(&table->philo[0]), free_table(table), 0);
	table->start_time = get_time_in_ms();
	create_philo(table);
	create_threads(table);
	while (wait(NULL) != -1)
		;
	sem_post(table->print);
	free_table(table);
	return (0);
}
