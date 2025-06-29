/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:57:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 09:17:35 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dest;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (n > ft_strlen(str))
	{
		printf("strndup : n > strlen(str)\n");
		return (NULL);
	}
	dest = malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
	{
		perror("strndup : malloc");
		return (NULL);
	}
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	// 文字が '\0' の場合は文字列終端も検索対象
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*combine_str_and_free_oldstr(char *str1, char *str2)
{
	char	*dest;

	dest = ft_strjoin(str1, str2);
	if (dest == NULL)
		exit(1);
	free(str1);
	free(str2);
	return (dest);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	if (dst == NULL || src == NULL)
		return ((size_t)(-1));
	i = 0;
	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	while (i < src_size && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}
