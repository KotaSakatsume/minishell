/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 08:23:24 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_cmd *parse_cmd(t_token **tok)
{
	t_cmd *cmd;
	cmd = mk_t_cmd();

	t_redirect *head = NULL;
	t_redirect *tail = NULL;

	advance_redirect(tok,&head,&tail,&cmd);
	advance_cmd(tok,&cmd);
	advance_redirect(tok,&head,&tail,&cmd);

	// コマンド名がなければ構文エラー + 位置表示する
	if (cmd->argc == 0)
	{
		if(tok != NULL && *tok!= NULL)//毎回これになる
			fprintf(stderr, "parse error: 予期しないトークン'%s'周辺に構文エラーがあります\n" , (*tok)->value);
		exit(1);
	}
	return cmd;
}

t_pipeline *parse_pipeline(t_token **tok)
{
	t_pipeline *head;
	t_pipeline *tail;
	t_pipeline *node;

	head = NULL;
	tail = NULL;
	do {
		node = mk_t_pipeline();
		node->cmd = parse_cmd(tok);

		if (!head)
			head = tail = node;
		else
		{
			tail->next = node;
			tail = node;
		}
	} while (accept_token(tok, TYPE_PIPE));	// '|' が続く限りループ

	return (head);
}

t_job *parse_job(t_token **tok)
{
	t_job *job;

	job = mk_t_job();
	job->pipeline = parse_pipeline(tok);

	if(accept_token(tok, TYPE_SEMICOLON) ||  (tok != NULL && *tok == NULL))
		job->sep = SEP_SEQ;
	else
		job->sep = SEP_NONE;

	job->next = NULL;
	return (job);
}

t_job *parse_line(t_token **tokens_top)
{
	t_job	*head = NULL;
	t_job	*tail = NULL;
	t_job	*job_ptr;
	t_token **cur = tokens_top;

	while (cur && *cur) // && (*cur)->status->token_type != TYPE_EOF
	{
		job_ptr = parse_job(cur);
		if (head == NULL)
			head = tail = job_ptr;
		else
		{
			tail->next = job_ptr;
			tail = job_ptr;
		}
	}
	return (head);
}
