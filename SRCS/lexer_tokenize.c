/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:08:24 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/14 14:35:32 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialize_t_token(t_token *t_token_node)
{
	t_token_node->id = -1;
	t_token_node->marge_id = -1;
	t_token_node->value = NULL;
	t_token_node->status = NULL;
	t_token_node->next = NULL;
}

void initialize_t_token_stat(t_token_stat *t_token_stat_node)
{
	t_token_stat_node->token_type = TYPE_INITIAL;
	t_token_stat_node->in_quote = QUOTE_INITIAL;
	t_token_stat_node->need_expand = -1;
	t_token_stat_node->after_space_is = -1;
}

void set_after_space(t_token *t_token_node, int after_space_exist)
{
	t_token_node->status->after_space_is = after_space_exist;
}

int strlrn(char *str)
{
	int len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char *ft_strndup(char *str, int n)
{
	int i;
	char *dest;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (n > strlen(str))
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

t_token *mk_t_token(char *start_ptr, char *end_ptr, int mode)
{
	t_token *t_token_node;
	t_token_node = malloc(sizeof(t_token));
	if (t_token_node == NULL)
	{
		perror("mk_t_token : malloc");
		return (NULL);
	}
	initialize_t_token(t_token_node);
	t_token_node->value = ft_strndup(start_ptr, end_ptr - start_ptr);
	if (t_token_node->value == NULL)
	{
		free(t_token_node);
		return (NULL);
	}
	t_token_node->status = malloc(sizeof(t_token_stat));
	if (t_token_node->status == NULL)
	{
		perror("mk_t_token : malloc");
		free(t_token_node->value);
		free(t_token_node);
		return (NULL);
	}
	initialize_t_token_stat(t_token_node->status);

	if (mode == mode_single_quote)
	{

		t_token_node->status->in_quote = QUOTE_SINGLE;
	}
	else if (mode == mode_double_quote)
	{

		t_token_node->status->in_quote = QUOTE_DOUBLE;
	}
	else if (mode == mode_normal)
	{

		t_token_node->status->in_quote = QUOTE_OUT;
	}
	else
	{
		perror("mk_t_token : mode is not valid");
		exit(1);
	}

	return (t_token_node);
}

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

t_token **lexer_tokenize(char *input)
{
	print_teststr("start_tokenize");
	t_token **dest;
	dest = malloc(sizeof(t_token *) * (1));
	if (dest == NULL)
	{
		perror("lexer_tokenize : malloc");
		return (NULL);
	}
	*dest = NULL;

	char *start_ptr;
	char *end_ptr;
	t_token *t_token_node_ptr;
	int mode;
	int after_space_exist;

	while (is_space(*input))
		input++;
	while (*input != '\0')
	{
		start_ptr = input;
		after_space_exist = 0;
		if (*input == '\'')
			mode = mode_single_quote;
		else if (*input == '"')
			mode = mode_double_quote;
		else
			mode = mode_normal;

		end_ptr = serach_end_ptr(input, mode);
		if (end_ptr == NULL)
		{
			// NULLのとき、続けて読みとり
			// free構造体all
			print_teststr("detect : continue");
			exit(1);
			return (NULL);
		}
		t_token_node_ptr = mk_t_token(start_ptr, end_ptr, mode);
		if (t_token_node_ptr == NULL)
		{
			// エラー処理
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
