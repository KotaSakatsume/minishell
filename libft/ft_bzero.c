/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:37:26 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 21:03:50 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
// int	main(void)
// {
// 	char str1[50] = "Hello, World! This is a test string.";
// 	char str2[50] = "Hello, World! This is a test string.";

// 	printf("Before ft_bzero: %s\n", str1);
// 	ft_bzero(str1, 6);
// 	printf("After ft_bzero: %s\n", str1);

// 	bzero(str2, 6);
// 	printf("After bzero: %s\n", str2);

// 	return (0);
// }