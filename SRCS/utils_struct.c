/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:16:12 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 19:30:15 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_token_cont(t_token **dest)
{
	t_token *next;
	int i;
	next = *dest;
	i = 0;
	
	while(next != NULL)
	{
		i++;
		next = next->next;
	}
	return (i);
}
