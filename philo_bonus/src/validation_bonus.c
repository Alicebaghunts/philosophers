/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 14:55:59 by alisharu          #+#    #+#             */
/*   Updated: 2025-05-29 14:55:59 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_valid_number(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		len++;
		if (len > 11)
			return (0);
		i++;
	}
	if (ft_atol(str) >= 1 && ft_atol(str) <= INT_MAX)
		return (1);
	return (0);
}

static int	ft_isdigit(int ch)
{
	return (ch >= '0' && ch <= '9');
}

static int	has_only_valid_chars(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if ((argv[i][j] == '+' || argv[i][j] == '-') && argv[i][j + 1])
			j++;
		if (!argv[i][j])
			return (0);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
	}
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	int		i;
	char	*arg;

	i = 0;
	while (++i < argc)
	{
		arg = argv[i];
		if (!is_valid_number(arg))
			return (error_handling(INVALID_NUMBER), 0);
	}
	return (1);
}

int	validation(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_handling(INVALID_ARGUMENT), 0);
	if (!has_only_valid_chars(argc, argv))
		return (error_handling (INVALID_SYMBOLS), 0);
	if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > 500)
		return (error_handling(INVALID_PHILO_COUNT), 0);
	if (validate_arguments(argc, argv) == 0)
		return (0);
	return (1);
}
