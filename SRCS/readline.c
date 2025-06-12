/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/10 20:20:53 by kosakats         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	*shell_env_ptr;
	t_env		*env_list;
	char		*input;
	char		*tmp;
	char		*concat;

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
		{ // CtrlD(EOF)
			printf("exit_Ctrl_D\n");
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
				// KOUBUNKAISEKI
				// continue ;
			}
			add_history(input);
		}
		// rl_redisplay();
		// printf("check_input: %s\n", input);
		free(input);
	}
	return (0);
}
