/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:21:46 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 11:40:02 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = strnlen(s, n);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	const char	*original = "Hello, World!";
// 	char		*copy;

// 	copy = ft_strndup(original, 5);
// 	if (copy)
// 	{
// 		printf("Copied string: %s\n", copy); // "Hello" と表示される
// 		free(copy);                          // メモリを解放
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}
// 	return (0);
// }
