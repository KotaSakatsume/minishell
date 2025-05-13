/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:04:14 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 10:51:21 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		neg;
	long	num;

	len = get_num_length(n);
	str = malloc(sizeof(char) * (len + 1));
	num = n;
	neg = 0;
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	while (len > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = ft_itoa(123345678);
// 	if (str)
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	str = ft_itoa(-456);
// 	if (str)
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	str = ft_itoa(0);
// 	if (str)
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	return (0);
// }
