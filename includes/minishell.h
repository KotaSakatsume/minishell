/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:50:31 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/14 13:58:16 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

// for_error
# define ERROR_ARGS 1

// for_utils
# define mode_single_quote 1
# define mode_double_quote 2
# define mode_normal 0

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
	int marge_id;			 // スペースの有無から、コマンド結合グループ作成
} t_token_stat;

typedef struct s_token
{
	int id;				  // 管理ID
	char *value;		  // トークンの値
	t_token_stat *status; // 詳細項目
	struct s_token *next; // 次のt_token(連結リスト)
} t_token;

// lexer_tokenize.c
t_token **lexer_tokenize(char *input);

// set_token_vals.c
void set_token_vals(t_token **head);

// print_token.c
void print_token(t_token **head);
void print_teststr(char* str);

// serch_end_ptr.c
char *serach_end_ptr(char *input, int mode);

// utils.c
int is_space(char c);

#endif
