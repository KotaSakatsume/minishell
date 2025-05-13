/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:35:59 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 21:04:10 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}
// int	main(void)
// {
// 	int	num;

// 	num = 'a';
// 	printf("%c\n", ft_toupper(num));
// 	return (0);
// }
