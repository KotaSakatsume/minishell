/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_to_stoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:38:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/07 16:56:44 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_stat *mk_token_stat(str)
{
	t_token_stat *dest;
	dest = malloc(sizeof(t_token_stat));
	if(dest == NULL)
	{
		perror("mk_token_stat : malloc");
		return (NULL);
	}
	dest->token_type = 0;
	dest->in_quote = 0;
	dest->need_expand = 0;
	dest->after_space_is = 0;
	dest->marge_id = 0;
	return (dest);
}

t_token *mk_stoken_node(char *str , int id)
{
	t_token *dest;

	dest = malloc(sizeof(t_token));
	if(dest == NULL)
	{
		perror("mk_stoken_node : malloc");
		return (NULL);
	}
	dest->id = id;
	dest->value = str;
	dest->status = mk_token_status(str);
	if(dest->status == NULL)
	{
		perror("mk_stoken_node : set_status");
		//free(dest);
		return (NULL);
	}
	dest->next = NULL;
	return (dest);
}

int cnv_splited_to_stoken(char **dest , t_token **head_pp)
{
	int i;
	t_token stoken_node;
	t_token *tail;
	
	i = 0;
	while(dest[i] != NULL)
	{
		if(*head_pp == NULL)
		{
			*head_pp = mk_stoken_node(dest[i] , i);
		}
		else
		{
			tail = serch_tail(*head_pp);
		}
		
	}
}