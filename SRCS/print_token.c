/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:38:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/13 19:14:36 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token **head)
{

	const char *token_type_str[] = {
	"TYPE_INITIAL",
	"TYPE_WORD",
	"TYPE_PIPE",
	"TYPE_REDIRECT_IN",
	"TYPE_REDIRECT_OUT",
	"TYPE_REDIRECT_APPEND",
	"TYPE_REDIRECT_HEREDOC",
	"TYPE_QUOTE_SINGLE",
	"TYPE_QUOTE_DOUBLE",
 	"TYPE_EOF"
	};

	const char *quote_type_str[] = {
		"QUOTE_INITIAL",
		"QUOTE_OUT",
		"QUOTE_SINGLE",
		"QUOTE_DOUBLE"
	};

	if (head == NULL)
	{
		perror("print_token: head is NULL");
		return;
	}
	t_token *node_ptr;
	node_ptr = *head;
	while (node_ptr != NULL)
	{
		printf("\nid	: %d\n|  value	: %s\n|  type		: %s\n|  in_quote	: %s\n|  need_expand	: %d\n|  after_space	: %d\n|  marge_id	: %d\n\n",
			   node_ptr->id, node_ptr->value, token_type_str[node_ptr->status->token_type], quote_type_str[node_ptr->status->in_quote], node_ptr->status->need_expand, node_ptr->status->after_space_is, node_ptr->status->marge_id);
		node_ptr = node_ptr->next;
	}
}