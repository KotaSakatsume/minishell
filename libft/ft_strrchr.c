/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:45:01 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 21:12:30 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	if ((char)c == '\0')
		return ((char *)&str[len]);
	while (len--)
	{
		if (str[len] == (unsigned char)c)
			return ((char *)&str[len]);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*result;
// 	char	*a;

// 	result = ft_strrchr("Hello, World!", '\0');
// 	a = strrchr("Hello, World!", '\0');
// 	printf("Test 3: %p\n", result);
// }
