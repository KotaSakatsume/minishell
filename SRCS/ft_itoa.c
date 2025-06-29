/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:49 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:45:29 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_nreverse(char *str, size_t str_size)
{
	size_t	i;
	char	temp;

	i = 0;
	while (str_size / 2 > i)
	{
		temp = str[str_size - 1 - i];
		str[str_size - 1 - i] = str[i];
		str[i] = temp;
		i++;
	}
}

static size_t	cal_strsize(int n)
{
	size_t	str_size;

	str_size = 0;
	if (n < 0)
		str_size++;
	while (n != 0)
	{
		str_size++;
		n /= 10;
	}
	return (str_size);
}

static void	mal_pad(char *dest, int n)
{
	size_t	i;
	size_t	minus_flag;

	i = 0;
	minus_flag = 0;
	if (n < 0)
	{
		minus_flag = 1;
		n *= -1;
	}
	while (n != 0)
	{
		dest[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (minus_flag)
	{
		dest[i] = '-';
		i++;
	}
	dest[i] = '\0';
}

static char	*itoa_corners(int n)
{
	char	*dest;

	if (n == 0)
	{
		dest = malloc(2);
		if (dest == NULL)
			return (NULL);
		ft_strlcpy(dest, "0", 2);
		return (dest);
	}
	if (n == INT_MIN)
	{
		dest = malloc(12);
		if (dest == NULL)
			return (NULL);
		ft_strlcpy(dest, "-2147483648", 12);
		return (dest);
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	str_size;

	str_size = 0;
	if (n == INT_MIN || n == 0)
	{
		dest = itoa_corners(n);
		return (dest);
	}
	str_size = cal_strsize(n);
	dest = malloc(str_size + 1);
	if (dest == NULL)
		return (NULL);
	mal_pad(dest, n);
	str_nreverse(dest, str_size);
	return (dest);
}
