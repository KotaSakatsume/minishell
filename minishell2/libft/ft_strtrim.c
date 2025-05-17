/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:11:55 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 10:48:07 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	new_len;
	char	*result;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = len - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	new_len = end - start + 1;
	result = (char *)malloc(new_len + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, s1 + start, new_len);
	result[new_len] = '\0';
	return (result);
}

// int	main(void)
// {
// 	const char	*s1 = "   Hello World!   ";
// 	char		*trimmed;
// 	const char	*set = " ";

// 	trimmed = ft_strtrim(s1, set);
// 	if (trimmed)
// 	{
// 		printf("Trimmed string: '%s'\n", trimmed);
// 		free(trimmed);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed!\n");
// 	}
// 	return (0);
// }
