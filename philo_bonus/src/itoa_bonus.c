/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <alisharu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:52:24 by alisharu          #+#    #+#             */
/*   Updated: 2025-06-05 13:52:24 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_malloc_size(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i < len)
		++i;
	return (i);
}

static char	*ft_malloc(int size)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * size);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

static int	dig_len(int n)
{
	int	temp;
	int	len;

	temp = n;
	len = 0;
	while (temp != 0)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

static char	*changeing(int n, int negative)
{
	int		len;
	char	*str;

	len = dig_len(n);
	if (negative == -1)
		len++;
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n != 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (negative == -1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		negative;
	char	*str;

	negative = 1;
	if (n < 0)
	{
		negative = -1;
		if (n != -2147483648)
			n = -n;
		else
			return (ft_substr("-2147483648", 0, 11));
	}
	if (n == 0)
		return (ft_substr("0", 0, 11));
	str = changeing(n, negative);
	return (str);
}
