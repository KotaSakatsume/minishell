/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:16:58 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/17 16:13:26 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// for_error
# define ERROR_ARGS 1
//リダイレクト
# define REDIRECT_IN 1      // <
# define REDIRECT_OUT 2     // >
# define REDIRECT_APPEND 3  // >>
# define REDIRECT_HEREDOC 4 // <<

// def_struct
typedef enum token_type
{
	TYPE_WORD,             //  else
	TYPE_PIPE,             //  |
	TYPE_REDIRECT_IN,      //  >
	TYPE_REDIRECT_OUT,     //  <
	TYPE_REDIRECT_APPEND,  //  >>
	TYPE_REDIRECT_HEREDOC, //  <<
	TYPE_QUOTE_SINGLE,     //  ‘
	TYPE_QUOTE_DOUBLE,     //  “
	TYPE_SEMICOLON,        //  ;
	TYPE_EOF               //
}			t_token_type;

typedef enum in_quote
{
	QUOTE_OUT,    //
	QUOTE_SINGLE, //  ‘
	QUOTE_DOUBLE  //  “
}			t_in_quote;

typedef struct s_token_stat
{
	t_token_type token_type; // トークンのタイプ
	t_in_quote in_quote;     // 何のクオート内にいるかどうか
	int need_expand;         // 変数展開の必要があるかどうか
	int after_space_is;      // 後ろにスペースがあるかどうか

}			t_token_stat;

typedef struct s_token
{
	int id;               // 管理ID
	char *value;          // トークンの値
	int token_marge_id;   // スペースの有無から、コマンド結合グループ作成
	t_token_stat *status; // 詳細項目
	struct s_token *next; // 次のt_token(連結リスト)
}			t_token;

//実行部分の構造体
typedef struct s_redirect
{
	char *file_name;         // リダイレクト対象のファイル名
	int type;                // リダイレクトの種類 (例: <, >, >>, <<)
	struct s_redirect *next; // 複数のリダイレクト対応のためのリンクリスト
}			t_redirect;

typedef struct s_command
{
	char *cmd_name;         // コマンド名 (例: ls, grep)
	char **args;            // 引数リスト (例: ["ls", "-l", NULL])
	int cmd_marge_id;       // スペースの有無から、コマンド結合グループ作成
	t_redirect *redirects;  // リダイレクト情報のリスト
	struct s_command *next; // パイプライン用に次のコマンドへのポインタ
}			t_command;

//環境変数と終了ステータス
typedef struct s_shell_env
{
	char **envp;     // 環境変数を格納する配列
	int exit_status; // 終了ステータス
}			t_shell_env;

void		execution_minishell(t_token *head, t_shell_env *t_shell_env);
// t_command	*parse_tokens_to_commands(t_token *tokens);
void		print_command_info(t_command *cmd);
t_command	*parse_tokens_to_commands(t_token *tokens);

#endif