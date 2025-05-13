```
#ifndef MINISHELL_H
# define MINISHELL_H

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
	int token_marge_id;            // スペースの有無から、コマンド結合グループ作成
}			t_token_stat;

typedef struct s_token
{
	int id;               // 管理ID
	char *value;          // トークンの値
	t_token_stat *status; // 詳細項目
	struct s_token *next; // 次のt_token(連結リスト)
}			t_token;

//環境変数と終了ステータス
typedef struct s_shell_env
{
	char **envp;     // 環境変数を格納する配列
	int exit_status; // 終了ステータス
}			t_shell_env;
```

