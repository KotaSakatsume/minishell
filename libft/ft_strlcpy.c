/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:53:36 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 17:41:36 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strlen(char *str)
// {
// 	int	count;

// 	count = 0;
// 	while (str[count] != '\0')
// 	{
// 		count++;
// 	}
// 	return (count);
// }

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

// int	main(void)
// {
// 	const char	*src = "Hello, World!";
// 	char		dest[10];
// 	size_t		length;

// 	length = ft_strlcpy(dest, src, sizeof(dest));
// 	printf("Copied: %s\n", dest);
// 	printf("Length: %zu\n", length);
// 	return (0);
// }
