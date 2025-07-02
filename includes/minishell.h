/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/02 15:37:50 by kosakats         ###   ########.fr       */
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
# define MODE_NORMAL 0
# define MODE_SINGLE_QUOTE 1
# define MODE_DOUBLE_QUOTE 2
# define MODE_SEMICOLON 3
# define MODE_PIPE 4
# define MODE_REDIRECT_IN 5
# define MODE_REDIRECT_OUT 6
# define MODE_REDIRECT_APPEND 7
# define MODE_REDIRECT_HEREDOC 8

typedef enum token_type
{
	TYPE_INITIAL,
	TYPE_WORD,
	TYPE_PIPE,
	TYPE_REDIRECT_IN,
	TYPE_REDIRECT_OUT,
	TYPE_REDIRECT_APPEND,
	TYPE_REDIRECT_HEREDOC,
	TYPE_QUOTE_SINGLE,
	TYPE_QUOTE_DOUBLE,
	TYPE_SEMICOLON,
	TYPE_EOF
}								t_token_type;

typedef enum in_quote
{
	QUOTE_INITIAL,
	QUOTE_OUT,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}								t_in_quote;

typedef struct s_token_stat
{
	t_token_type				token_type;
	t_in_quote					in_quote;
	int							need_expand;
	int							after_space_is;
}								t_token_stat;

typedef struct s_token
{
	int							id;
	int							marge_id;
	char						*value;
	t_token_stat				*status;
	struct s_token				*next;
}								t_token;

// Paser struct

typedef enum e_seq_type
{
	SEP_NONE,
	SEP_SEQ,
	SEP_AND,
	SEP_OR
}								t_seq_type;

typedef struct s_redirect
{
	t_token_type				type;
	char						*filename;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_cmd
{
	char						**argv;
	int							argc;
	t_token						**token;
	t_redirect					*redir;
}								t_cmd;

typedef struct s_pipeline
{
	t_cmd						*cmd;
	struct s_pipeline			*next;
}								t_pipeline;

typedef struct s_job
{
	t_pipeline					*pipeline;
	t_seq_type					sep;
	struct s_job				*next;
}								t_job;

// global struct
extern volatile sig_atomic_t	g_sigatm;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_shell_env
{
	t_env						*env_list;
	char						**envp;
	int							exit_status;
	int							exit_status_now;
}								t_shell_env;

// signal_handle.c
void							get_signal(int signo);
void							display_newline_in_readline(int signo);
void							set_signal_for_readline(void);
void							set_signal_default(void);

// mk_shell_env.c
t_shell_env						*mk_shell_env(char **envp);

// env list
t_env							*env_to_list(char **envp);

// readline_seq.c
char							*readline_seq(t_shell_env *t_shellenv_ptr);

// lexer.c
t_token							**lexer(char *line);

// lexer_tokenize.c
t_token							**lexer_tokenize(char *input);
void							initialize_t_token(t_token *t_token_node);

// lexer_set_token_vals.c
void							lexer_set_token_vals(t_token **head);

// lexer_set_token_stat_vals.c
void							set_token_stat_vals(
									t_token_stat *token_stat_ptr,
									char *token_str);
void							set_stat_token_type(
									t_token_stat *token_stat_ptr,
									char *token_str);
void							set_stat_token_need_expand(
									t_token_stat *token_stat_ptr);
void							set_stat_token_in_quote(
									t_token_stat *token_stat_ptr,
									char *token_str);

// print_for_debag.c
void							print_token(t_token **head);
void							print_teststr(char *str);
void							print_shell_env(t_shell_env *shell_env_ptr);
void							dump_jobs(t_job *job);

// serch_end_ptr.c
char							*serach_end_ptr(char *input);

// utils_1.c
int								is_space(char c);
char							*ft_strjoin(char *s1, char *s2);
int								ft_strncmp(char *s1, char *s2, int n);
int								ft_strcmp(char *s1, char *s2);
int								ft_strlen(char *str);

// utils_2.c
char							*ft_strdup(char *s);
char							*ft_strndup(char *str, int n);
char							*ft_strchr(const char *s, int c);
char							*combine_str_and_free_oldstr(char *str1,
									char *str2);

// utils_3.c
char							**ft_split(char const *s, char c);
size_t							ft_strlcpy(char *dst, char *src,
									size_t dstsize);

// utils_4.c
char							*ft_strnstr(const char *big, const char *little,
									size_t len);
char							*ft_strstr(const char *haystack,
									const char *needle);
void							*ft_realloc(void *ptr, size_t old_size,
									size_t new_size);

// ft_itoa.c
char							*ft_itoa(int n);

// utils_struct.c
int								check_token_cont(t_token **dest);
void							free_alltoken_ptr(t_token *dest);
void							update_pipeline_node(t_pipeline **head,
									t_pipeline **tail, t_pipeline *node);
void							update_job_list(t_job **head, t_job **tail,
									t_job *job_ptr);

// utils_mk_struct.c
t_cmd							*mk_t_cmd(void);
t_job							*mk_t_job(void);
t_pipeline						*mk_t_pipeline(void);
t_redirect						*mk_t_redirect(void);
t_token							*mk_t_token(char *start_ptr, char *end_ptr);

// utilis_free_struct.c
void							free_all_token(t_token **dest);
void							free_token(t_token *free_dest);
void							free_conjunc_token(t_token **dest);

// utils_initialize_struct.c
void							initialize_t_token(t_token *t_token_node);
void							initialize_t_token_stat(
									t_token_stat *t_token_stat_node);

// mk_shell_env.c
t_shell_env						*mk_shell_env(char **envp);

// marge_same_margeid_token.c
void							marge_same_margeid_token(t_token **split_token);

// paser_utils.c
bool							accept_token(t_token **token,
									t_token_type type);
void							advance_token(t_token **token);
void							expect_token(t_token **tok, t_token_type type);
bool							check_token(t_token **token, t_token_type type);

// parse.c
t_job							*parse_line(t_token **tokens_top,
									t_shell_env *t_shellenv_ptr);

// parse_free_utils
void							free_all_job(t_job *job_node);
void							free_all_pipeline(t_pipeline *pipeline_node);
void							free_all_cmd(t_cmd *cmd_node);

// parse_advance
t_cmd							*parse_cmd(t_token **tok,
									t_shell_env *t_shellenv_ptr);
int								advance_redirect(t_token **tok,
									t_redirect **head, t_redirect **tail,
									t_cmd **cmd);
int								advance_cmd(t_token **tok, t_cmd **cmd);

// expander.c
void							expander(t_job *job_head,
									t_shell_env *t_shellenv_ptr);

// extend_daller.c
void							extend_daller(t_pipeline *pipeline_ptr,
									t_shell_env *t_shellenv_ptr);

// extend_daller_check_and_expand_mode.c
void							check_and_expand_question_mode(
									char *daller_str_ptr,
									t_token *token_ptr,
									t_shell_env *t_shellenv_ptr);
void							check_and_expand_normal_mode(
									char *daller_str_ptr,
									t_token *token_ptr,
									t_shell_env *t_shellenv_ptr);
void							check_and_expand_daller_mode(
									char *daller_str_ptr,
									t_token *token_ptr);

// expander_utils.c
void							fx_extend_to_all_pipeline(t_job *job_head,
									void (*extend)(t_pipeline *));
void							fx_extend_to_all_pipeline_with_env(
									t_job *job_head,
									t_shell_env *t_shellenv_ptr,
									void (*extend)(t_pipeline *,
										t_shell_env *));
t_token							*mk_empty_token(void);

// expander_quote_and_backslash.c
void							delete_quote_cmd(t_pipeline *pipeline_ptr);
void							set_token_remove_quote(t_token *next_token_ptr);
void							set_token_remove_backslash(
									t_token *next_token_ptr,
									int count_backslash_to_remove);
int								check_token_remove_backslash(
									t_token *next_token_ptr);

// expander_nospace.c
void							combine_main(t_pipeline *pipeline_ptr);
int								count_resized_token_len(t_token **token);
void							pad_dest(t_token **dest, int len,
									t_token **token);
void							free_olddest(t_token **token_head);

// expander_token_to_cmd
void							exchange_token_to_char(t_job *job_head);
void							token_to_char_pipeline(t_job *job_ptr);
void							token_to_char_cmd(t_pipeline *pipeline_ptr);

// exec
void							ft_exec(t_job *job_head,
									t_shell_env *shell_envp);
void							free_env_list(t_env *head);

void							update_exit_status(t_shell_env *shell_env,
									int status);
void							execute(char **av, t_shell_env *shell_env);
void							handle_redirects(t_redirect *redir,
									t_shell_env *shell_env);
void							handle_external(t_pipeline *pipeline,
									t_shell_env *shell_env, int prev_pipe[2],
									int pipe_fd[2]);
void							process_heredocs(t_pipeline *pipeline,
									t_shell_env *shell_env);

// exec
void							free_envp(char **envp);
void							free_paths(char **paths);
// builtin
void							handle_builtin(t_pipeline *pipeline,
									t_shell_env *shell_env, int prev_pipe[2],
									int pipe_fd[2]);
void							builtin_cd(char **av, t_shell_env *shell_env);
void							builtin_echo(char **args);
void							builtin_env(char **argv, t_shell_env **head,
									t_shell_env *shell_env);
void							builtin_exit(char **args);
void							builtin_export(char **av,
									t_shell_env *shell_env);
void							builtin_pwd(t_env **env_list,
									t_shell_env *shell_env);
void							builtin_unset(char **args, t_env **env_list,
									t_shell_env *shell_env);
t_env							*env_to_list(char **envp);
void							free_envp_array(char **envp, int count);
char							*get_env_value(t_env *env_list, char *key);
void							ft_error(void);
char							**allocate_envp_array(int count);
void							update_exit_status(t_shell_env *shell_env,
									int status);
char							*create_env_entry(char *key, char *value);
char							*ft_strcpy(char *dst, const char *src);
char							*ft_strncat(char *dest, const char *src,
									size_t n);
void							validate_heredoc_delimiter(char *delimiter,
									t_shell_env *shell_env);

// builtin_utils
void							safe_free(void *ptr);
void							free_string_array(char **arr);
t_env							*get_env_by_key(char *key, t_env *env_list);
void							free_env_node(t_env *node);
int								is_valid_key(const char *key);

// find_path
char							*find_path(char *cmd, char **envp);
char							*join_path_and_cmd(char *path, char *cmd);

#endif
