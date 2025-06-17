/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/18 08:22:03 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void advance_token(t_token **token)
{
	if(token == NULL)
	{
		fprintf(stderr, "parse error:advance_token\n");
		exit (1);
	}
	*token = (*token)->next;
}

bool accept_token(t_token **token, t_token_type type)
{
	if(token != NULL && *token != NULL && (*token)->status->token_type == type)
	{
		advance_token(token);
		return (true);
	}
	return (false);
}

bool check_token(t_token **token, t_token_type type)
{
	if(token != NULL && *token != NULL && (*token)->status->token_type == type)
	{
		return (true);
	}
	return (false);
}

void expect_token(t_token **tok, t_token_type type)
{
	if (!accept_token(tok, type)) {
		fprintf(stderr, "parse error: expected %d\n", type);
		exit(1);
	}
}
