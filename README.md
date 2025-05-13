```
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

// for_error
# define ERROR_ARGS 1

// def_struct
typedef enum token_type
{
TYPE_WORD,//  else
TYPE_PIPE,//  |
TYPE_REDIRECT_IN,//  >
TYPE_REDIRECT_OUT,//  <
TYPE_REDIRECT_APPEND,//  >>
TYPE_REDIRECT_HEREDOC,//  <<
TYPE_QUOTE_SINGLE,//  ‘
TYPE_QUOTE_DOUBLE,//  “
TYPE_EOF//
} t_token_type;

typedef enum in_quote
{
QUOTE_OUT,//
QUOTE_SINGLE,//  ‘
QUOTE_DOUBLE//  “
} t_in_quote;

typedef struct s_token_stat
{
t_token_typetoken_type;// トークンのタイプ
t_in_quotein_quote;// 何のクオート内にいるかどうか
intneed_expand;// 変数展開の必要があるかどうか
intafter_space_is;// 後ろにスペースがあるかどうか
intmarge_id;// スペースの有無から、コマンド結合グループ作成
} t_token_stat;

typedef struct s_token
{
intid;// 管理ID
char *value;// トークンの値
t_token_stat*status;// 詳細項目
struct s_token*next;// 次のt_token(連結リスト)
} t_token;

//lexer_split.c
char **lexer_split(char *input);

#endif```
