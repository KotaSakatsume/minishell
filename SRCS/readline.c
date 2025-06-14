/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/14 11:59:24 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *input, t_shell_env *shell_env_ptr)
{
	t_token	**split_token;
	t_job	*job_head;

	split_token = lexer_tokenize(input);
	if (split_token == NULL)
	{
		return (READLINE_CONTINUE);
	}
	lexer_set_token_vals(split_token); //一部expanderの内容も実装してしまった
	// marge_same_margeid_token(split_token); //これはexpanderで実装
	// print_token(split_token);
	// 以下パーサー実行部分
	job_head = parse_line(split_token);
	//　以下パーサーの結果表示部分
	// dump_jobs(job_head);
	// jobに入らなかったtokenをfreeする必要あり
	// 作成中のEXPANDER
	// expander(job_head);
	// dump_jobs(job_head);
	ft_exec(job_head, shell_env_ptr);
	// ★ここでテスト可能★
	// print_shell_evn(shell_env_ptr);
	// TODO: split_tokenのメモリ解放を実装
	return (READLINE_EXIT);
}

//シグナル追加
void	handle_sigint(int signo)
{
	(void)signo;
	// Ctrl-C の処理: プロンプトを再表示
	write(STDOUT_FILENO, "\n", 1);
	// update_exit_status(shell_env, 130); // 実行失敗
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void	handle_sigquit(int signo)
// {
// 	(void)signo;
// 	return ;
// 	// Ctrl-\ の処理: 何もしない
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	*shell_env_ptr;
	t_env		*env_list;
	char		*input;
	char		*tmp;
	char		*concat;

	// シグナルハンドラーを設定 kosakats追加
	signal(SIGINT, handle_sigint); // Ctrl-C の処理
	signal(SIGQUIT, SIG_IGN);
	shell_env_ptr = mk_shell_env(envp);
	shell_env_ptr->env_list = env_to_list(shell_env_ptr->envp);
	if (shell_env_ptr == NULL)
	{
		perror("main: mk_shell_env failed");
		exit(1);
	}
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
		{ // Ctrl-D (EOF)
			printf("exit\n");
			break ;
		}
		if (*input != '\0')
		{
			while (lexer(input, shell_env_ptr) == READLINE_CONTINUE)
			{
				tmp = readline(" > ");
				concat = ft_strjoin(input, tmp);
				free(tmp);
				free(input);
				input = concat;
			}
			// printf("exit_status: %d\n", shell_env_ptr->exit_status);
			add_history(input);
		}
		free(input);
	}
	return (0);
}
