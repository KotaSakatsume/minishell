/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:51:27 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 18:51:44 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_all_token (t_token **dest)
{
	t_token *now_token;
	t_token *next_token;

	next_token = *dest;

	if(next_token != NULL)
	{
		now_token = next_token;
		next_token = now_token->next;
		free_token(now_token);
	}
	free(dest);
}

void free_token(t_token* free_dest)
{
	if(free_dest->value != NULL)
		free(free_dest->value);
	if(free_dest->status != NULL)
		free(free_dest->status);
	free(free_dest);
}