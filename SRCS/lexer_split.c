/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:08:24 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/07 13:12:32 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int strlrn(char *str)
{
	int len;

	len = 0;
	if (str == NULL)
		return (0);
	while(str[len] != '\0')
		len++;
	return (len);
}

char* ft_strndup(char *str, int n)
{
	int i;
	char* dest;

	i = 0;
	if(str == NULL)
		return (NULL);
	if(n > strlen(str))
	{
		printf("strndup : n > strlen(str)\n");
		return (NULL);
	}
	dest = malloc(sizeof(char) * (n + 1));
	if(dest == NULL)
	{
		perror("strndup : malloc");
		return (NULL);
	}
	while(i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void all_free(char **dest , int num)
{
	int i;

	i = 0;
	while(i < num)
	{
		free(dest[i]);
		i++;
	}
}

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void rep_malloc(char **dest , char *input)
{
	int i;
	int str_len;
		
	i = 0;

	while(*input != '\0')
	{
		while(is_space(*input))
			input++;
		if(*input != '\0')
		{
			str_len = 0;
			while(!is_space(input[str_len]) && input[str_len] != '\0')
				str_len++;
			dest[i] = ft_strndup(input , str_len);
			if(dest[i] == NULL)
			{
				all_free(dest , i);
				return ;
			}
			input = input + str_len;
			i++;
		}
	}
	return ;
}


int word_count(char *input)
{
	int ans;

	ans = 0;
	while(is_space(*input))
		input++;
	while(*input != '\0')
	{
		while(!is_space(*input) && *input != '\0')
			input++;
		ans++;
		while(is_space(*input) && *input != '\0')
			input++;
	}
	return (ans);
}

char **lexer_split(char *input)
{
	printf ("start_split\n");
	int word_num;
	char **dest;

	word_num = word_count(input);
	printf ("word_num = %d\n", word_num);
	dest = malloc(sizeof(char *) * (word_num + 1));
	if(dest == NULL)
	{
		perror("lexer_split : malloc");
		return (NULL);
	}
	dest[word_num] = NULL;
	rep_malloc(dest,input);
	return (dest);
}
