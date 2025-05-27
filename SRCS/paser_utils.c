/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/27 17:54:24 by mkuida           ###   ########.fr       */
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

t_cmd *mk_t_cmd()
{
	t_cmd* dest;
	dest = malloc(1*sizeof(t_cmd));
	if(dest == NULL)
		exit(1);
	dest->argv = NULL;
	dest->argc = 0;
	dest->redir = NULL;
	return (dest);
}

t_job *mk_t_job()
{
	t_job* dest;
	dest = malloc(1*sizeof(t_job));
	if(dest == NULL)
		exit(1);
	dest->pipeline = NULL;
	dest->sep = SEP_NONE;
	dest->next = NULL;
	return (dest);
}

// void expect_token(t_token **token, t_token_type type)
// {
// 	if
// }