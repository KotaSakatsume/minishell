/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:43:30 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 11:04:15 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str[] = "ABC";

// 	// char	*str1;
// 	// char	*str2;
// 	// str1 = "HelloWorld";
// 	// str2 = "";
// 	// printf("%d", ft_strncmp(str1, str2, 1));
// 	printf("ABC: ABD   = %d\n", ft_strncmp(str, "ABD", 2));
// 	printf("ABC: ABC   = %d\n", ft_strncmp(str, "ABC", 2));
// 	printf("ABC: AAA   = %d\n", ft_strncmp(str, "AAA", 2));
// 	printf("ABC: ABCD  = %d\n", ft_strncmp(str, "ABCD", 2));
// 	printf("ABC: AB    = %d\n", ft_strncmp(str, "AB", 2));
// 	printf("ABC: B     = %d\n", ft_strncmp(str, "B", 2));
// 	printf("ABC: A     = %d\n", ft_strncmp(str, "A", 2));
// 	return (0);
// }
