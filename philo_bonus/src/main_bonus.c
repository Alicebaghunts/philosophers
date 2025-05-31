/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 15:13:15 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 15:13:15 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		index;

	index = 0;
	if (validation(argc, argv) == 0)
		return (0);
	table = init_table(argc, argv);
	if (table->philo_count == 1)
		return (one_philo_pick_fork(&table->philo[0]), free_table(table), 0);
	table->start_time = get_time_in_ms();
	create_philo(table);
	free_table(table);
	while (wait(NULL) != -1)
		;
	return (0);
}
