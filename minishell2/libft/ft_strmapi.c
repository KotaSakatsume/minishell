/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:46:07 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 11:10:35 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_strlen(char const *str)
// {
// 	int	count;

// 	count = 0;
// 	while (str[count] != '\0')
// 	{
// 		count++;
// 	}
// 	return (count);
// }

// static char	to_upper(unsigned int index, char c)
// {
// 	if (index % 2 == 0)
// 		return (c - 32);
// 	return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*result;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s);
	result = (char *)malloc(len + 1);
	if (!result)
	{
		return (NULL);
	}
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}

// int	main(void)
// {
// 	const char	*str = "hello world";
// 	char		*modified_str;

// 	modified_str = ft_strmapi(str, to_upper);
// 	if (modified_str)
// 	{
// 		printf("Original string: %s\n", str);
// 		printf("Modified string: %s\n", modified_str);
// 		free(modified_str);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed!\n");
// 	}
// 	return (0);
// }
