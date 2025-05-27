/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/27 16:20:26 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void advance_token(t_token **token)
{
	*token = (*token)->next;
}

bool accept_token(t_token **token, t_token_type type)
{
	if(*token != NULL && (*token)->status->token_type == type)
	{
		advance_token(token);
		return (true);
	}
	return (false);
}

// void expect_token(t_token **token, t_token_type type)
// {
// 	if
// }