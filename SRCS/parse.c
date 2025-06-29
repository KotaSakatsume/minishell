/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 16:18:07 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pipeline_node(t_pipeline **head, t_pipeline **tail,
		t_pipeline *node)
{
	if (*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}

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

static void	update_job_list(t_job **head, t_job **tail, t_job *job_ptr)
{
	if (*head == NULL)
	{
		*tail = job_ptr;
		*head = *tail;
	}
	else
	{
		(*tail)->next = job_ptr;
		*tail = job_ptr;
	}
}

static void	free_all_token_ptr(t_token *dest)
{
	t_token	*now_token;
	t_token	*next_token;

	now_token = dest;
	while (now_token != NULL)
	{
		next_token = now_token->next;
		free_token(now_token);
		now_token = next_token;
	}
}

static int	set_next_token_null(t_token *tokens_top, t_token *target_ptr)
{
	t_token *now_token = tokens_top;

	if(now_token == target_ptr)
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
	printf("error at set_next_token_null\n");
	exit (1);
}

t_job	*parse_line(t_token **tokens_top, t_shell_env *t_shellenv_ptr)
{
	t_job	*head;
	t_job	*tail;
	t_job	*job_ptr;
	t_token	**cur;
	t_token	*token_top_ptr;

	token_top_ptr = *tokens_top;
	head = NULL;
	tail = NULL;
	cur = tokens_top;
	while (cur && *cur)
	{
		job_ptr = parse_job(cur, t_shellenv_ptr);
		update_job_list(&head, &tail, job_ptr);
		fflush(stdout);
		if (t_shellenv_ptr->exit_status == 2)
		{
			if(set_next_token_null(token_top_ptr,*cur) == 1)
			{
				t_shellenv_ptr->exit_status = 3;
				free_all_token(tokens_top);
				return(head);
			}
			free_all_token_ptr(*cur);
			*tokens_top = token_top_ptr;
			return (head);
		}
	}
	*tokens_top = token_top_ptr;
	t_shellenv_ptr->exit_status = 0;
	return (head);
}
