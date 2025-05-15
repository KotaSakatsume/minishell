/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:50:31 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/15 14:03:54 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

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

#endif
