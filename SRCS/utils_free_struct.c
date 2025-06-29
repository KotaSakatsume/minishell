/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:51:27 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:27:21 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_token(t_token **dest)
{
	t_token	*now_token;
	t_token	*next_token;

	now_token = *dest;
	while (now_token != NULL)
	{
		next_token = now_token->next;
		free_token(now_token);
		now_token = next_token;
	}
	free(dest);
}

void	free_token(t_token *free_dest)
{
	if (free_dest->value != NULL)
	{
		free(free_dest->value);
		free_dest->value = NULL;
	}
	if (free_dest->status != NULL)
	{
		free(free_dest->status);
		free_dest->status = NULL;
	}
	free(free_dest);
	free_dest = NULL;
}

static bool	token_stat_type_is_conjunc(t_token_type t_type)
{
	if (t_type == TYPE_PIPE || t_type == TYPE_REDIRECT_IN
		|| t_type == TYPE_REDIRECT_OUT || t_type == TYPE_REDIRECT_APPEND
		|| t_type == TYPE_REDIRECT_HEREDOC || t_type == TYPE_SEMICOLON)
		return (true);
	else
		return (false);
}

static bool	token_stat_type_is_red(t_token_type t_type)
{
	if (t_type == TYPE_REDIRECT_IN || t_type == TYPE_REDIRECT_OUT
		|| t_type == TYPE_REDIRECT_APPEND || t_type == TYPE_REDIRECT_HEREDOC)
		return (true);
	else
		return (false);
}

void	free_conjunc_token(t_token **dest)
{
	t_token	*now_token;
	t_token	*next_token;
	bool	flag_red;
	bool	flag_after_red;

	next_token = *dest;
	flag_after_red = false;
	while (next_token != NULL)
	{
		now_token = next_token;
		flag_red = token_stat_type_is_red(now_token->status->token_type);
		// printf("now_token_type : %d\n",now_token->status->token_type);
		next_token = now_token->next;
		// printf("next_token = %p\n",next_token);
		if (token_stat_type_is_conjunc(now_token->status->token_type) == true
			|| flag_after_red == true)
		{
			// printf("delete = %s\n", now_token->value);
			// fflush(stdout);
			free_token(now_token);
		}
		flag_after_red = flag_red;
	}
	free(dest);
}
