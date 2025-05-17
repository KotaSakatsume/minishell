/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:45:25 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/08 23:34:06 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strcpy(char *dest, const char *src, int offset)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[offset + i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1, 0);
	ft_strcpy(result, s2, s1_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strjoin("hello", "world"));
// 	return (0);
// }
