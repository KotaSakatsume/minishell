/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 14:04:36 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_cmd *parse_cmd(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_cmd *cmd;

	cmd = mk_t_cmd();
	t_redirect *head = NULL;
	t_redirect *tail = NULL;
	if(advance_redirect(tok,&head,&tail,&cmd) != 0)
	{
		t_shellenv_ptr->exit_status = 2;
		return (NULL);
	}
	advance_cmd(tok,&cmd);
	advance_redirect(tok,&head,&tail,&cmd);
	if (cmd->argc == 0)
	{
		printf("parse error: 構文エラーがあります (cmd)\n");
		return (NULL);
	}
	return (cmd);
}

static t_pipeline *parse_pipeline(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_pipeline *head;
	t_pipeline *tail;
	t_pipeline *node;

	head = NULL;
	tail = NULL;
	do {
		node = mk_t_pipeline();
		node->cmd = parse_cmd(tok,t_shellenv_ptr);
		if(node->cmd == NULL)
			return (NULL);
		if (!head)
			head = tail = node;
		else
		{
			tail->next = node;
			tail = node;
		}
	} while (accept_token(tok, TYPE_PIPE));
	return (head);
}

static t_job *parse_job(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_job *job;

	job = mk_t_job();
	job->pipeline = parse_pipeline(tok, t_shellenv_ptr);
	if(job->pipeline == NULL)
	{
		return (NULL);
	}

	if(accept_token(tok, TYPE_SEMICOLON) ||  (tok != NULL && *tok == NULL))
		job->sep = SEP_SEQ;
	else
		job->sep = SEP_NONE;

	job->next = NULL;
	return (job);
}

t_job *parse_line(t_token **tokens_top, t_shell_env *t_shellenv_ptr)
{
	t_job	*head;
	t_job	*tail;
	t_job	*job_ptr;
	t_token **cur;

	head = NULL;
	tail = NULL;
	cur = tokens_top;
	while (cur && *cur)
	{
		job_ptr = parse_job(cur, t_shellenv_ptr);
		if (job_ptr == NULL)
			return (NULL);
		if (head == NULL)
			head = tail = job_ptr;
		else
		{
			tail->next = job_ptr;
			tail = job_ptr;
		}
	}
	t_shellenv_ptr->exit_status = 0;
	return (head);
}
