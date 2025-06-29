/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:57:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 09:19:37 by mkuida           ###   ########.fr       */
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
