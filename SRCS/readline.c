/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 17:22:41 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lexer(char *input, t_shell_env *shell_env_ptr)
{
	t_token **split_token;

	split_token = lexer_tokenize(input);
	if (split_token == NULL)
	{
		return (READLINE_CONTINUE);
	}
	lexer_set_token_vals(split_token);
	print_token(split_token);
	// 以下パーサー実行部分
	t_job *job_head;
	job_head = parse_line(split_token);

	//　以下パーサーの結果表示部分
	// dump_jobs(job_head);

	// jobに入らなかったtokenをfreeする必要あり
	// 作成中のEXPANDER
	expander(job_head);
	dump_jobs(job_head);
	// ★ここでテスト可能★
	// print_shell_evn(shell_env_ptr);
	// TODO: split_tokenのメモリ解放を実装
	
	return (READLINE_EXIT);
}

int main(int argc, char **argv, char **envp)
{
	t_shell_env *shell_env_ptr;

	shell_env_ptr = mk_shell_env(envp);
	if (shell_env_ptr == NULL)
	{
		perror("main: mk_shell_env failed");
		exit (1);
	}
	

	while (1)
	{
		char *input = readline("minishell > ");
		if (!input)
		{ // CtrlD(EOF)
			printf("exit_Ctrl_D\n");
			break;
		}
		if (*input != '\0')
		{
			while (lexer(input, shell_env_ptr) == READLINE_CONTINUE)
			{
				char *tmp = readline(" > ");
				char *concat = ft_strjoin(input, tmp);
				free(tmp);
				free(input);
				input = concat;
			}
			add_history(input);
		}
		// rl_redisplay();
		// printf("check_input: %s\n", input);
		free(input);
	}
	return (0);
}
