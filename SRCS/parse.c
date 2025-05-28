/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/29 00:05:49 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_cmd *parse_cmd(t_token **tok)
{
	t_cmd *cmd;
	cmd = mk_t_cmd();

	// コマンド名＋引数
	while (*tok && (*tok)->status->token_type == TYPE_WORD) {
		// argv を伸長
		cmd->argv = realloc(cmd->argv, sizeof(char*)*((cmd->argc)+2)); // tyuui
		cmd->token = realloc(cmd->token, sizeof(t_token*)*((cmd->argc)+2));

		cmd->argv[cmd->argc] = ft_strdup((*tok)->value);	// tyuui
		cmd->token[cmd->argc] = *tok;

		cmd->argc++;

		cmd->argv[cmd->argc]= NULL;
		cmd->token[cmd->argc]= NULL;

		advance_token(tok);
	}

	t_redirect *head = NULL;
	t_redirect *tail = NULL;
	
	// リダイレクト
	while (*tok)
	{
		t_token_type tt = (*tok)->status->token_type;
		if (tt == TYPE_REDIRECT_IN || tt == TYPE_REDIRECT_OUT || tt == TYPE_REDIRECT_APPEND || tt == TYPE_REDIRECT_HEREDOC)
		{
			t_redirect *r = calloc(1, sizeof(*r));
			r->type = tt;
			advance_token(tok);                       // '>' や '>>' を消費
			// expect_token(tok, TYPE_WORD);             // 次はファイル名
			if(*tok == NULL || (*tok)->status->token_type != TYPE_WORD)
			{
				perror("at adter redirect please word");
				exit(-1);
			}
			r->filename = strdup((*tok)->value);
			advance_token(tok);                       // ファイル名を消費

			// リストに追加
			if(head == NULL)
			{
			//	r->next = cmd->redir;
				head = tail = r;
				cmd->redir = r;
			}
			else
			{
				tail->next = r;
				tail = r;
			}
		}
		else
			break;
	}

	// コマンド名がなければ構文エラー + 位置表示する
	if (cmd->argc == 0) {
		fprintf(stderr, "parse error: empty command\n");
		exit(1);
	}
	return cmd;
}

t_pipeline *parse_pipeline(t_token **tok)
{
	t_pipeline *head;
	t_pipeline *tail;

	head = NULL;
	tail = NULL;
	do {
		t_pipeline *node = calloc(1, sizeof(*node));
		node->cmd  = parse_cmd(tok);
		node->next = NULL;

		if (!head)
			head = tail = node;
		else
		{
			tail->next = node;
			tail = node;
		}
	} while (accept_token(tok, TYPE_PIPE));  // '|' が続く限りループ

	return (head);
}

t_job *parse_job(t_token **tok)
{
	t_job *job;

	job = mk_t_job();
	job->pipeline = parse_pipeline(tok);

	// セパレータ設定
	if(accept_token(tok, TYPE_SEMICOLON))
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
