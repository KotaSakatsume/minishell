/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:52:01 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 21:03:58 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memmove(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			dest[i - 1] = src[i - 1];
			i--;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	str1[20] = "Hello, World!";
// 	char	str2[20] = "aaaaaaaaaaaaaaaaaa";

// 	ft_memmove(str1, str2, 7);
// 	printf("%s\n", str1);
// 	return (0);
// }
