/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:50:31 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/27 20:18:25 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// for_error
#define ERROR_ARGS 1

// for_readline_continue
#define READLINE_EXIT 0
#define READLINE_CONTINUE 1

// for_utils
#define mode_normal 0
#define mode_single_quote 1
#define mode_double_quote 2
#define mode_semicolon 3
#define mode_pipe 4
#define mode_redirect_in 5
#define mode_redirect_out 6
#define mode_redirect_append 7
#define mode_redirect_heredoc 8

// def_struct
typedef enum token_type
{
	TYPE_INITIAL,
	TYPE_WORD,			   //  else
	TYPE_PIPE,			   //  |
	TYPE_REDIRECT_IN,	   //  >
	TYPE_REDIRECT_OUT,	   //  <
	TYPE_REDIRECT_APPEND,  //  >>
	TYPE_REDIRECT_HEREDOC, //  <<
	TYPE_QUOTE_SINGLE,	   //  '
	TYPE_QUOTE_DOUBLE,	   //  "
	TYPE_SEMICOLON,		   //  ;
	TYPE_EOF			   //
} t_token_type;

typedef enum in_quote
{
	QUOTE_INITIAL,
	QUOTE_OUT,	  //
	QUOTE_SINGLE, //  '
	QUOTE_DOUBLE  //  "
} t_in_quote;

typedef struct s_token_stat
{
	t_token_type token_type; // トークンのタイプ
	t_in_quote in_quote;	 // 何のクオート内にいるかどうか
	int need_expand;		 // 変数展開の必要があるかどうか
	int after_space_is;		 // 後ろにスペースがあるかどうか
} t_token_stat;

typedef struct s_token
{
	int id;				  // 管理ID
	int marge_id;		  // スペースの有無から、コマンド結合グループ作成
	char *value;		  // トークンの値
	t_token_stat *status; // 詳細項目
	struct s_token *next; // 次のt_token(連結リスト)
} t_token;

// Paser struct

typedef enum e_seq_type
{
	SEP_NONE, // 未設定初期値、使用しない
	SEP_SEQ,  // “;” または 文末（これのみ使用予定）
	SEP_AND,  // “&&”（使用なし、一応BONUS拡張できるように＆BASH構造理解のため形だけ）
	SEP_OR	  // “||”（使用なし、一応BONUS拡張できるように＆BASH構造理解のため形だけ）
} t_seq_type;

typedef struct s_redirect
{
	t_token_type type;		 // 　４種類のenum（>,>>,<,<<）※lexerで使用したenumの再利用
	char *filename;			 // 　リダイレクト先ファイル名
	struct s_redirect *next; // 　次リダイレクト設定（NULL終端）
} t_redirect;

typedef struct s_cmd
{
	char **argv;	   // NULL 終端の文字列配列 argv[0] = cmd_name argv[1]以降はオプション
	int argc;		   // argvの要素数
	t_redirect *redir; // リダイレクトリスト
} t_cmd;

typedef struct s_pipeline
{
	t_cmd *cmd;				 // 先頭コマンド
	struct s_pipeline *next; // パイプ接続された次のコマンド(あれば)
} t_pipeline;

typedef struct s_job
{
	t_pipeline *pipeline; // ひとまとまりのパイプライン
	t_seq_type sep;		  // 次の job との区切り
	struct s_job *next;	  // 次のシーケンス要素(あれば)
} t_job;

// 環境変数と終了ステータス
typedef struct s_shell_env
{
	char **envp;	 // 環境変数を格納する配列
	int exit_status; // 終了ステータス
} t_shell_env;

// lexer_tokenize.c
t_token **lexer_tokenize(char *input);

// lexer_set_token_vals.c
void lexer_set_token_vals(t_token **head);

// print_for_debag.c
void print_token(t_token **head);
void print_teststr(char *str);
void print_shell_env(t_shell_env *shell_env_ptr);
void dump_jobs(t_job *job);

// serch_end_ptr.c
char *serach_end_ptr(char *input);

// utils.c
int is_space(char c);
char *ft_strjoin(char const *s1, char const *s2);
int ft_strncmp(char *s1, char *s2, int n);
int ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);

// mk_shell_env.c
t_shell_env *mk_shell_env(char **envp);

// marge_same_margeid_token.c
void marge_same_margeid_token(t_token **split_token);

// paser_utils.c
bool accept_token(t_token **token, t_token_type type);
void advance_token(t_token **token);
void expect_token(t_token **tok, t_token_type type);
t_cmd *mk_t_cmd();
t_job *mk_t_job();
char	*ft_strdup(char *s);

//parse.c
t_job *parse_line(t_token **tokens_top);

#endif
