/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_initialize_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:34:28 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 17:34:56 by mkuida           ###   ########.fr       */
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
