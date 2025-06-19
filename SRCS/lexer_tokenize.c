/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:08:24 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 19:08:17 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void into_list(t_token **head, t_token *t_token_node_ptr)
{
	t_token *ptr;
	if (*head == NULL)
		*head = t_token_node_ptr;
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = t_token_node_ptr;
	}
}

void set_after_space(t_token *t_token_node, int after_space_exist)
{
	t_token_node->status->after_space_is = after_space_exist;
}

t_token **pad_t_token_dptr(t_token **dest, char *input)
{
	char *start_ptr;
	char *end_ptr;
	t_token *t_token_node_ptr;
	int after_space_exist;

	while (*input != '\0')
	{
		start_ptr = input;
		after_space_exist = 0;
		end_ptr = serach_end_ptr(input);
		if (end_ptr == NULL) // read_continue
		{
			free_all_token(dest);
			return (NULL);
		}
		t_token_node_ptr = mk_t_token(start_ptr, end_ptr);
		if (t_token_node_ptr == NULL)
		{
			free_all_token(dest);
			return (NULL);
		}
		input = end_ptr;
		while (is_space(*input))
		{
			after_space_exist = 1;
			input++;
		}
		set_after_space(t_token_node_ptr, after_space_exist);
		into_list(dest, t_token_node_ptr);
	}
	return (dest);
}

void all_free(char **dest, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(dest[i]);
		i++;
	}
}

void rep_malloc(char **dest, char *input)
{
	int i;
	int str_len;

	i = 0;

	while (*input != '\0')
	{
		while (is_space(*input))
			input++;
		if (*input != '\0')
		{
			str_len = 0;
			while (!is_space(input[str_len]) && input[str_len] != '\0')
				str_len++;
			dest[i] = ft_strndup(input, str_len);
			if (dest[i] == NULL)
			{
				all_free(dest, i);
				return;
			}
			input = input + str_len;
			i++;
		}
	}
	return;
}

int word_count(char *input)
{
	int ans;

	ans = 0;
	while (is_space(*input))
		input++;
	while (*input != '\0')
	{
		while (!is_space(*input) && *input != '\0')
			input++;
		ans++;
		while (is_space(*input) && *input != '\0')
			input++;
	}
	return (ans);
}

t_token **lexer_tokenize(char *input)
{
	t_token **dest;

	while (is_space(*input))
		input++;
	if (*input == '\0')
		return (NULL);
	dest = malloc(sizeof(t_token *) * (1));
	if (dest == NULL)
	{
		perror("lexer_tokenize : malloc");
		return (NULL);
	}
	*dest = NULL;

	if (pad_t_token_dptr(dest, input) == NULL)
		return (NULL);
	return (dest);
}
