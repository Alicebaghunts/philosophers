/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:12 by miaghabe          #+#    #+#             */
/*   Updated: 2025/05/20 18:06:09 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handling(int num)
{
	if (num == 1)
		printf("\033[31mError: Invalid argument\e[0m\n");
	else if (num == 2)
		printf("\033[31mError: Invalid symbols\e[0m\n");
	else if (num == 3)
		printf("\033[31mError: Invalid philosopher count\e[0m\n");
	else if (num == 4)
		printf("\033[31mError: Isn't valid number\e[0m\n");
	else if (num == 5)
		printf("\033[31mError: Could't calloc memory\e[0m\n");
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			len;
	size_t			i;

	len = size * count;
	if (len == 0)
		return (malloc(1));
	if (len / size != count)
		return (NULL);
	ptr = (unsigned char *)malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
