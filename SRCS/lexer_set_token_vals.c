/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_token_vals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 16:54:05 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_id(t_token **head)
{
	int		i;
	t_token	*node_ptr;

	i = 0;
	if (head == NULL || *head == NULL)
		return ;
	node_ptr = *head;
	while (node_ptr != NULL)
	{
		node_ptr->id = i;
		node_ptr = node_ptr->next;
		i++;
	}
}


static int	set_token_marge_id(t_token *current_token_ptr, int marge_id)
{
	current_token_ptr->marge_id = marge_id;
	marge_id++;
	if (current_token_ptr->status->token_type == TYPE_WORD
		&& current_token_ptr->status->after_space_is == 0)
	{
		if (current_token_ptr->next != NULL
			&& current_token_ptr->next->status->token_type == TYPE_WORD)
			marge_id--;
	}
	return (marge_id);
}

void	lexer_set_token_vals(t_token **head)
{
	char	*token_str;
	t_token	*next_token_ptr;
	int		marge_id;

	next_token_ptr = *head;
	marge_id = 0;
	set_id(head);
	while (next_token_ptr != NULL)
	{
		token_str = next_token_ptr->value;
		set_token_stat_vals(next_token_ptr->status, token_str);
		next_token_ptr = next_token_ptr->next;
	}
	next_token_ptr = *head;
	while (next_token_ptr != NULL)
	{
		marge_id = set_token_marge_id(next_token_ptr, marge_id);
		next_token_ptr = next_token_ptr->next;
	}
}
