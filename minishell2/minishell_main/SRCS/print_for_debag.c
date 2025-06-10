/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_debag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:38:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/08 19:39:34 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token **head)
{

	const char *token_type_str[] = {
	"TYPE_INITIAL",
	"TYPE_WORD",
	"TYPE_PIPE",
	"TYPE_REDIRECT_IN",
	"TYPE_REDIRECT_OUT",
	"TYPE_REDIRECT_APPEND",
	"TYPE_REDIRECT_HEREDOC",
	"TYPE_QUOTE_SINGLE",
	"TYPE_QUOTE_DOUBLE",
 	"TYPE_EOF"
	};

	const char *quote_type_str[] = {
		"QUOTE_INITIAL",
		"QUOTE_OUT",
		"QUOTE_SINGLE",
		"QUOTE_DOUBLE"
	};

	if (head == NULL)
	{
		perror("print_token: head is NULL");
		return;
	}
	t_token *node_ptr;
	node_ptr = *head;
	while (node_ptr != NULL)
	{
		printf("\nid	: %d\n|  marge_id	: %d\n|  value	: %s\n|  type		: %s\n|  in_quote	: %s\n|  need_expand	: %d\n|  after_space	: %d\n\n",
			   node_ptr->id,node_ptr->marge_id,node_ptr->value, token_type_str[node_ptr->status->token_type], quote_type_str[node_ptr->status->in_quote], node_ptr->status->need_expand, node_ptr->status->after_space_is);
		node_ptr = node_ptr->next;
	}
}

void print_teststr(char* str)
{
	printf("------------------\n|%s|\n------------------\n", str);
	return;
}

void print_shell_env(t_shell_env *shell_env_ptr)
{
	int i;

	i = 0;
	printf("exit_status	: %d\n", shell_env_ptr->exit_status);
	while(shell_env_ptr->envp[i] != NULL)
	{
		printf("envp[%d]	: %s\n", i, shell_env_ptr->envp[i]);
		i++;
	}
	return;
}


// 以下Paser
// シーケンス区切りタイプを文字列化
static const char *seq_type_str(t_seq_type s) {
    switch (s) {
        case SEP_NONE: return "NONE";
        case SEP_SEQ:  return "SEQ";
        case SEP_AND:  return "AND";
        case SEP_OR:   return "OR";
    }
    return "UNKNOWN";
}

// リダイレクトタイプを文字列化
static const char *redir_type_str(t_token_type t) {
    switch (t) {
        case TYPE_REDIRECT_IN:      return "<";
        case TYPE_REDIRECT_OUT:     return ">";
        case TYPE_REDIRECT_APPEND:  return ">>";
        case TYPE_REDIRECT_HEREDOC: return "<<";
        default:                    return "?!";
    }
}

// リダイレクトリストをダンプ
static void dump_redirects(t_redirect *r) {
    while (r) {
        printf("      [redir] %s  \"%s\"\n",
               redir_type_str(r->type),
               r->filename);
        r = r->next;
    }
}

// コマンド（argv + redir）をダンプ
static void dump_cmd(t_cmd *c) {
    printf("    [cmd] argv[%d]:", c->argc);
    for (int i = 0; i < c->argc; i++) {
        printf(" %s", c->argv[i]);
		printf("(id=%d)", c->token[i]->id);
    }
    printf("\n");
    dump_redirects(c->redir);
}

// パイプラインをダンプ
static void dump_pipeline(t_pipeline *p) {
    int idx = 0;
    while (p) {
        printf("  [pipe %d]\n", idx++);
        dump_cmd(p->cmd);
        p = p->next;
    }
}

// ジョブ（シーケンス要素）をダンプ
void dump_jobs(t_job *job) {
    int jid = 0;
    while (job) {
        printf("[job %d] sep=%s\n", jid++, seq_type_str(job->sep));
        dump_pipeline(job->pipeline);
        job = job->next;
    }
}

