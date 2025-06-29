/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:57:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 12:01:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
