/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:51:51 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:51:51 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	else if (num == 6)
		printf("\033[31mError: Could't init semaphore\e[0m\n");
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

char	*ft_strdup(char *src)
{
	char	*s;
	int		i;

	s = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (src && src[i])
	{
		s[i] = src[i];
		++i;
	}
	s[i] = 0;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)malloc((get_malloc_size(s, start, len) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
