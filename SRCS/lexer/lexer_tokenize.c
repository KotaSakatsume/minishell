/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:08:24 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 17:07:35 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	into_list(t_token **head, t_token *t_token_node_ptr)
{
	t_token	*ptr;

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

static t_token	*make_token_and_check(char *start_ptr, char **input,
		t_token ***dest)
{
	char	*end_ptr;
	t_token	*token;

	end_ptr = serach_end_ptr(start_ptr);
	if (end_ptr == NULL)
	{
		free_all_token(*dest);
		return (NULL);
	}
	token = mk_t_token(start_ptr, end_ptr);
	if (token == NULL)
	{
		free_all_token(*dest);
		return (NULL);
	}
	*input = end_ptr;
	return (token);
}

static int	skip_space(char **input)
{
	int	after_space;

	after_space = 0;
	while (is_space(**input))
	{
		after_space = 1;
		(*input)++;
	}
	return (after_space);
}

t_token	**pad_t_token_dptr(t_token **dest, char *input)
{
	char	*start_ptr;
	t_token	*t_token_node_ptr;
	int		after_space_exist;

	while (*input != '\0')
	{
		start_ptr = input;
		t_token_node_ptr = make_token_and_check(start_ptr, &input, &dest);
		if (t_token_node_ptr == NULL)
			return (NULL);
		after_space_exist = skip_space(&input);
		t_token_node_ptr->status->after_space_is = after_space_exist;
		into_list(dest, t_token_node_ptr);
	}
	return (dest);
}

t_token	**lexer_tokenize(char *input)
{
	t_token	**dest;

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
