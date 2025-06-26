/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:57:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 17:26:09 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str)
	{
		perror("ft_strjoin malloc error\n");
		exit(1);
	}
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != '\0' || s2[i] != '\0')
		return (s1[i] - s2[i]);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

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

	// char	*temp;
	dest = ft_strjoin(str1, str2);
	if (dest == NULL)
	{
		exit(1);
	}
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

// split
static void	free_all(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static int	is_sep(char s, char c)
{
	return (s == c);
}

static int	get_word_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_sep(*str, c))
			str++;
		if (*str)
		{
			count++;
			while (*str && !is_sep(*str, c))
				str++;
		}
	}
	return (count);
}

static char	*allocate_word(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	i = 0;
	len = 0;
	while (s[len] && !is_sep(s[len], c))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**ret;
	int		i;

	words = get_word_count(s, c);
	ret = malloc(sizeof(char *) * (words + 1));
	i = 0;
	if (!ret)
		return (NULL);
	while (*s && i < words)
	{
		while (*s && is_sep(*s, c))
			s++;
		ret[i] = allocate_word(s, c);
		if (ret[i] == NULL)
		{
			free_all(ret);
			return (NULL);
		}
		while (*s && !is_sep(*s, c))
			s++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

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
