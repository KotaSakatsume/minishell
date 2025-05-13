/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_vals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/13 19:11:24 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_stat_token_type(t_token_stat *token_stat_ptr, char *token_str)
{
	if (token_str == NULL)
	{
		perror("set_stat_token_type : token_str is NULL");
		exit(1);
	}
	if (strcmp(token_str, "|") == 0)
		token_stat_ptr->token_type = TYPE_PIPE;
	else if (strcmp(token_str, ">") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_OUT;
	else if (strcmp(token_str, "<") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_IN;
	else if (strcmp(token_str, ">>") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_APPEND;
	else if (strcmp(token_str, "<<") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_HEREDOC;
	else if (strcmp(token_str, "'") == 0)
		token_stat_ptr->token_type = TYPE_QUOTE_SINGLE;
	else if (strcmp(token_str, "\"") == 0)
		token_stat_ptr->token_type = TYPE_QUOTE_DOUBLE;
	else
		token_stat_ptr->token_type = TYPE_WORD;
}

void set_id(t_token **head)
{
	int i;
	t_token *node_ptr;

	i = 0;
	if (head == NULL || *head == NULL)
		return;
	node_ptr = *head;
	while (node_ptr != NULL)
	{
		node_ptr->id = i;
		node_ptr = node_ptr->next;
		i++;
	}
}

void set_token_stat_vals(t_token_stat *token_stat_ptr, char *token_str)
{
	set_stat_token_type(token_stat_ptr, token_str);
	// set_stat_token_need_expand(token_stat_ptr);
}

void set_token_vals(t_token **head)
{
	char *token_str;
	t_token *next_token_ptr;
	next_token_ptr = *head;

	set_id(head);

	while (next_token_ptr != NULL)
	{
		token_str = next_token_ptr->value;
		set_token_stat_vals(next_token_ptr->status, token_str);
		next_token_ptr = next_token_ptr->next;
	}
}
