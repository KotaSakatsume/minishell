/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:10:26 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/08 23:34:21 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen((char *)src);
	if (size == 0)
		return (src_len);
	dest_len = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (i < size - dest_len - 1 && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// int	main(void)
// {
// 	size_t	total_length;

// 	total_length = ft_strlcat("hello", "world", sizeof(3));
// 	printf("全長: %zu\n", total_length);
// 	return (0);
// }
