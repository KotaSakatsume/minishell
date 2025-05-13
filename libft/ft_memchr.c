/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:12:30 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 20:49:20 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (const unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	int	str2;

// 	// char	str1[] = "abcd\0ef";
// 	str2 = 'c';
// 	printf("%p", ft_memchr(NULL, str2, 6));
// 	return (0);
// }
