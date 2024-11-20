/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:30:29 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/20 07:25:48 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libftprintf.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long long	n;
	int					count;

	count = 0;
	n = (unsigned long long)ptr;
	count += ft_putstr_fd("0x", fd);
	count += ft_puthex_fd(n, fd, 'x');
	return (count);
}
