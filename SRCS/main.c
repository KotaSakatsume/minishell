/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:08 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/20 04:13:07 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_state g_state;

int main()
{
	char *input;
	t_token **split_token;
	t_job *job_head;

	init_gstate();
	while(1)
	{
		input = readline_seq();
		add_history(input);
		split_token = lexer(input);
		//free(input)

		// 以下パーサー実行部分
		job_head = parse_line(split_token);
		//free(split token)

		// 作成中のEXPANDER
		expander(job_head);
		dump_jobs(job_head);
		// ★ここでテスト可能★
		// print_shell_evn(shell_env_ptr);
		// TODO: split_tokenのメモリ解放を実装
	}
}

// SIGINT (+Ctrl-C) ハンドラ
static void handle_sigint(int signo)
{
	(void)signo;
	g_state.sigint_received = 1;
	// プロンプト行を改行して出し直す
	rl_replace_line("",0);
	rl_on_nex_line();
	rl_redisplay();
}

void init_gstate()
{
	g_state.sigint_received = 0;
	g_state.child_pid = 0;
	g_state.sa_int.sa_flags = SA_RESTART;
	g_state.sa_int.sa_handler = handle_sigint;
	sigemptyset(&g_state.sa_int.sa_mask);
	if( sigaction(SIGINT,&(g_state.sa_int),NULL) == -1)
	{
		peerror("sigaction");
		exit(1);
	}
}