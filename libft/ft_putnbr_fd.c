/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:54:14 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 10:30:06 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recursive_fd(int n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_recursive_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	ft_putnbr_recursive_fd(n, fd);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int num = 123;
// 	ft_putnbr_fd(num, 1);
// 	return (0);
// }