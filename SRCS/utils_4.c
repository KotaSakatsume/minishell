/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:57:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 10:32:19 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 1;
			while (little[j] != '\0' && big[i + j] == little[j] && (i
					+ j) < len)
			{
				j++;
			}
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h = haystack;
	const char	*n = needle;

	if (!*needle) // needle が空文字列の場合
		return ((char *)haystack);
	while (*haystack)
	{
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (!*n) // needle の最後まで一致した場合
			return ((char *)haystack);
		haystack++;
	}
	return (NULL); // 見つからなかった場合
}

static void	copy_data(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;
	char	*src;
	char	*dst;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		exit(1);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	src = (char *)ptr;
	dst = (char *)new_ptr;
	copy_data(dst, src, copy_size);
	free(ptr);
	return (new_ptr);
}
