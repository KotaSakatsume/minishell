/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:36:59 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/20 07:26:48 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libftprintf.h"

static int	handle_format(const char fmt, va_list args)
{
	if (fmt == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (fmt == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (fmt == 'p')
		return (ft_putptr_fd(va_arg(args, void *), 1));
	else if (fmt == 'd' || fmt == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (fmt == 'u')
		return (ft_putnbr_u_fd(va_arg(args, unsigned int), 1));
	else if (fmt == 'x' || fmt == 'X')
		return (ft_puthex_fd(va_arg(args, unsigned int), 1, fmt));
	else if (fmt == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
			count += handle_format(str[++i], args);
		else
			count += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = "hell";
// 	ft_printf("Test 1: Single Character: %c\n", 'A');
// 	ft_printf("Test 2: String: %s\n", "Hello, World!");
// 	ft_printf("Test 3: Pointer: %p\n", &str);
// 	ft_printf("Test 4: Integer: %d\n", -42);
// 	ft_printf("Test 5: Unsigned: %u\n", 42);
// 	ft_printf("Test 6: Hexadecimal lowercase: %x\n", 255);
// 	ft_printf("Test 7: Hexadecimal uppercase: %X\n", 255);
// 	ft_printf("Test 8: Percent sign: %%\n");
// 	return (0);
// }
