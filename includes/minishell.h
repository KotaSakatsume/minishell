/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:50:31 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 12:59:14 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// for_error
# define ERROR_ARGS 1

// for_readline_continue
# define READLINE_EXIT 0
# define READLINE_CONTINUE 1

// for_utils
# define mode_normal 0
# define mode_single_quote 1
# define mode_double_quote 2
# define mode_semicolon 3
# define mode_pipe 4
# define mode_redirect_in 5
# define mode_redirect_out 6
# define mode_redirect_append 7
# define mode_redirect_heredoc 8

// def_struct

// lexer struct

typedef enum token_type
{
	TYPE_INITIAL,
	TYPE_WORD,             //  else
	TYPE_PIPE,             //  |
	TYPE_REDIRECT_IN,      //  >
	TYPE_REDIRECT_OUT,     //  <
	TYPE_REDIRECT_APPEND,  //  >>
	TYPE_REDIRECT_HEREDOC, //  <<
	TYPE_QUOTE_SINGLE,     //  '
	TYPE_QUOTE_DOUBLE,     //  "
	TYPE_SEMICOLON,        //  ;
	TYPE_EOF               //
}							t_token_type;

typedef enum in_quote
{
	QUOTE_INITIAL,
	QUOTE_OUT,    //
	QUOTE_SINGLE, //  '
	QUOTE_DOUBLE  //  "
}							t_in_quote;

typedef struct s_token_stat
{
	t_token_type token_type; // トークンのタイプ
	t_in_quote in_quote;     // 何のクオート内にいるかどうか
	int need_expand;         // 変数展開の必要があるかどうか
	int after_space_is;      // 後ろにスペースがあるかどうか
}							t_token_stat;

typedef struct s_token
{
	int id;               // 管理ID
	int marge_id;         // スペースの有無から、コマンド結合グループ作成
	char *value;          // トークンの値
	t_token_stat *status; // 詳細項目
	struct s_token *next; // 次のt_token(連結リスト)
}							t_token;

// Paser struct

typedef enum e_seq_type
{
	SEP_NONE, // 未設定初期値、使用しない
	SEP_SEQ,  // “;” または 文末（これのみ使用予定）
	SEP_AND,  // “&&”（使用なし、一応BONUS拡張できるように＆BASH構造理解のため形だけ）
	SEP_OR    // “||”（使用なし、一応BONUS拡張できるように＆BASH構造理解のため形だけ）
}							t_seq_type;

typedef struct s_redirect
{
	t_token_type type;       // 　４種類のenum（>,>>,<,<<）※lexerで使用したenumの再利用
	char *filename;          // 　リダイレクト先ファイル名
	struct s_redirect *next; // 　次リダイレクト設定（NULL終端）
}							t_redirect;

typedef struct s_cmd
{
	char **argv;       // NULL 終端の文字列配列 argv[0] = cmd_name argv[1]以降はオプション
	int argc;          // argvの要素数
	t_token **token;   // 試し
	t_redirect *redir; // リダイレクトリスト
}							t_cmd;

typedef struct s_pipeline
{
	t_cmd *cmd;              // 先頭コマンド
	struct s_pipeline *next; // パイプ接続された次のコマンド(あれば)
}							t_pipeline;

typedef struct s_job
{
	t_pipeline *pipeline; // ひとまとまりのパイプライン
	t_seq_type sep;       // 次の job との区切り
	struct s_job *next;   // 次のシーケンス要素(あれば)
}							t_job;

// global struct
typedef struct s_global_state
{
	// シグナルハンドラからメインに通知するフラグ
	volatile sig_atomic_t	sigint_received;
	// 必要なら子プロセスPID もここに入れておく
	volatile sig_atomic_t	child_pid;
	// SIGINT 用の sigaction 構造体
	struct sigaction		sa_int;
	// （将来 BONUS で SIGQUIT 用も必要なら同様に追加）
}							t_global_state;

// 環境変数と終了ステータス
typedef struct s_env
{
	char *key;          // 環境変数のキー
	char *value;        // 環境変数の値
	struct s_env *next; // 次のノード
}							t_env;

typedef struct s_shell_env
{
	t_env *env_list; // 環境変数を格納する配列
	char					**envp;
	int exit_status; // 終了ステータス
}							t_shell_env;

// 唯一のグローバル変数
extern t_global_state		g_state;

// mk_shell_env.c
t_shell_env					*mk_shell_env(char **envp);

// env list
t_env						*env_to_list(char **envp);

// readline_seq.c
char						*readline_seq(t_shell_env *t_shellenv_ptr);

// lexer.c
t_token						**lexer(char *line);

// lexer_tokenize.c
t_token						**lexer_tokenize(char *input);
void						initialize_t_token(t_token *t_token_node);

// lexer_set_token_vals.c
void						lexer_set_token_vals(t_token **head);

// print_for_debag.c
void						print_token(t_token **head);
void						print_teststr(char *str);
void						print_shell_env(t_shell_env *shell_env_ptr);
void						dump_jobs(t_job *job);

// serch_end_ptr.c
char						*serach_end_ptr(char *input);

// utils.c
int							is_space(char c);
char						*ft_strjoin(char const *s1, char const *s2);
int							ft_strncmp(char *s1, char *s2, int n);
int							ft_strcmp(char *s1, char *s2);
int							ft_strlen(char *str);
char						*ft_strdup(char *s);
char						*ft_strndup(char *str, int n);
char						*ft_strchr(const char *s, int c);
char						*combine_str_and_free_oldstr(char *str1,
								char *str2);
size_t						ft_strlcpy(char *dst, char *src, size_t dstsize);
char						**ft_split(char const *s, char c);
char						*ft_strnstr(const char *big, const char *little,
								size_t len);
char						*ft_strstr(const char *haystack,
								const char *needle);

// ft_itoa.c
char						*ft_itoa(int n);

// utils_struct.c
int							check_token_cont(t_token **dest);

// utils_mk_struct.c
t_cmd						*mk_t_cmd(void);
t_job						*mk_t_job(void);
t_pipeline					*mk_t_pipeline(void);
t_redirect					*mk_t_redirect(void);
t_token						*mk_t_token(char *start_ptr, char *end_ptr);

// utilis_free_struct.c
void						free_all_token(t_token **dest);
void						free_token(t_token *free_dest);

// utils_initialize_struct.c
void						initialize_t_token(t_token *t_token_node);
void						initialize_t_token_stat(t_token_stat *t_token_stat_node);

// mk_shell_env.c
t_shell_env					*mk_shell_env(char **envp);

// marge_same_margeid_token.c
void						marge_same_margeid_token(t_token **split_token);

// paser_utils.c
bool						accept_token(t_token **token, t_token_type type);
void						advance_token(t_token **token);
void						expect_token(t_token **tok, t_token_type type);
bool						check_token(t_token **token, t_token_type type);

// parse.c
t_job						*parse_line(t_token **tokens_top,
								t_shell_env *t_shellenv_ptr);

// parse_free_utils
void						free_all_job(t_job *job_node);
void						free_all_pipeline(t_pipeline *pipeline_node);
void						free_all_cmd(t_cmd *cmd_node);

// parse_advance
int							advance_redirect(t_token **tok, t_redirect **head,
								t_redirect **tail, t_cmd **cmd);
int							advance_cmd(t_token **tok, t_cmd **cmd);

// expander.c
void						expander(t_job *job_head,
								t_shell_env *t_shellenv_ptr);

// extend_daller.c
void						extend_daller(t_pipeline *pipeline_ptr,
								t_shell_env *t_shellenv_ptr);

// expander_utils.c
void						fx_extend_to_all_pipeline(t_job *job_head,
								void (*extend)(t_pipeline *));
void						fx_extend_to_all_pipeline_with_env(t_job *job_head,
								t_shell_env *t_shellenv_ptr,
								void (*extend)(t_pipeline *, t_shell_env *));
t_token						*mk_empty_token(void);

// expander_quote_and_backslash.c
void						delete_quote_cmd(t_pipeline *pipeline_ptr);
void						set_token_remove_quote(t_token *next_token_ptr);
void						set_token_remove_backslash(t_token *next_token_ptr,
								int count_backslash_to_remove);
int							check_token_remove_backslash(t_token *next_token_ptr);

// expander_nospace.c
void						combine_main(t_pipeline *pipeline_ptr);
int							count_resized_token_len(t_token **token);
void						pad_dest(t_token **dest, int len, t_token **token);
void						free_olddest(t_token **token_head);

// expander_token_to_cmd
void						exchange_token_to_char(t_job *job_head);
void						token_to_char_pipeline(t_job *job_ptr);
void						token_to_char_cmd(t_pipeline *pipeline_ptr);

// exec
void						ft_exec(t_job *job_head, t_shell_env *shell_envp);
void						free_env_list(t_env *head);
// void						print_env_list(t_env *head);
void						update_exit_status(t_shell_env *shell_env,
								int status);
void						execute(char **av, t_shell_env *shell_env);
void						handle_redirects(t_redirect *redir,
								t_shell_env *shell_env);
void						handle_external(t_pipeline *pipeline,
								t_shell_env *shell_env, int prev_pipe[2],
								int pipe_fd[2]);
void						process_heredocs(t_pipeline *pipeline,
								t_shell_env *shell_env);

// builtin
void						handle_builtin(t_pipeline *pipeline,
								t_shell_env *shell_env, int prev_pipe[2],
								int pipe_fd[2]);
void						builtin_cd(char **av, t_shell_env *shell_env);
void						builtin_echo(char **args);
void						builtin_env(char **argv, t_shell_env **head,
								t_shell_env *shell_env);
void						builtin_exit(char **args);
void						builtin_export(char **av, t_shell_env *shell_env);
void						builtin_pwd(t_env **env_list,
								t_shell_env *shell_env);
void						builtin_unset(char **args, t_env **env_list,
								t_shell_env *shell_env);
t_env						*env_to_list(char **envp);

#endif
