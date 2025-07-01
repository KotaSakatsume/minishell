/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/07/01 10:53:38 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipeline	*parse_pipeline(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_pipeline	*head;
	t_pipeline	*tail;
	t_pipeline	*node;
	bool		rep;

	rep = true;
	head = NULL;
	tail = NULL;
	while (rep == true)
	{
		node = mk_t_pipeline();
		node->cmd = parse_cmd(tok, t_shellenv_ptr);
		update_pipeline_node(&head, &tail, node);
		if (t_shellenv_ptr->exit_status == 2)
			return (head);
		rep = accept_token(tok, TYPE_PIPE);
	}
	return (head);
}

static t_job	*parse_job(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_job	*job;

	job = mk_t_job();
	job->pipeline = parse_pipeline(tok, t_shellenv_ptr);
	if (t_shellenv_ptr->exit_status == 2)
	{
		return (job);
	}
	if (accept_token(tok, TYPE_SEMICOLON) || (tok != NULL && *tok == NULL))
		job->sep = SEP_SEQ;
	else
		job->sep = SEP_NONE;
	job->next = NULL;
	return (job);
}

static int	set_next_token_null(t_token *tokens_top, t_token *target_ptr)
{
	t_token	*now_token;

	now_token = tokens_top;
	if (now_token == target_ptr)
		return (1);
	while (now_token && now_token->next)
	{
		if (now_token->next == target_ptr)
		{
			now_token->next = NULL;
			return (0);
		}
		now_token = now_token->next;
	}
	return (0);
}

static t_job	*pl_sup(t_token **tokens_top, t_shell_env *t_shellenv_ptr,
		t_job *he, t_job *ta)
{
	t_job	*job_ptr;
	t_token	**cur;
	t_token	*token_top_ptr;

	token_top_ptr = *tokens_top;
	cur = tokens_top;
	while (cur && *cur)
	{
		job_ptr = parse_job(cur, t_shellenv_ptr);
		update_job_list(&he, &ta, job_ptr);
		if (t_shellenv_ptr->exit_status == 2)
		{
			if (set_next_token_null(token_top_ptr, *cur) == 1)
			{
				t_shellenv_ptr->exit_status = 3;
				free_all_token(tokens_top);
				return (he);
			}
			free_alltoken_ptr(*cur);
			*tokens_top = token_top_ptr;
			return (he);
		}
	}
	*tokens_top = token_top_ptr;
	return (he);
}

t_job	*parse_line(t_token **tokens_top, t_shell_env *t_shellenv_ptr)
{
	t_job	*head;
	t_job	*tail;
	t_job	*dest;

	head = NULL;
	tail = NULL;
	dest = pl_sup(tokens_top, t_shellenv_ptr, head, tail);
	return (dest);
}
