/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marge_same_margeid_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:07:09 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/19 18:23:54 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void marge_token(t_token *current_token, t_token *next_token)
{
	char *new_str;
	new_str = ft_strjoin(current_token->value, next_token->value);

	free(current_token->value);
	current_token->value = new_str;

	current_token->status->after_space_is = next_token->status->after_space_is;
	current_token->value = ft_strjoin(current_token->value, next_token->value);
	free(next_token);
}

void marge_same_margeid_token(t_token **split_token)
{
	t_token *current_token;
	current_token = *split_token;
	
	while(current_token->next != NULL)
	{
		if(current_token->marge_id == current_token->next->marge_id)
			marge_token(current_token, current_token->next);
		current_token = current_token->next;
	}	
	return;
}