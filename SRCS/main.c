/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:08 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 14:29:41 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_state		g_state;

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

static void	init_gstate(void)
{
	g_state.sigint_received = 0;
	g_state.child_pid = 0;
	g_state.sa_int.sa_flags = SA_RESTART;
	g_state.sa_int.sa_handler = handle_sigint;
	sigemptyset(&g_state.sa_int.sa_mask);
	if (sigaction(SIGINT, &(g_state.sa_int), NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}

static t_shell_env	*init_tshellenv(char **envp)
{
	t_shell_env	*t_shellenv_ptr;

	t_shellenv_ptr = mk_shell_env(envp);
	if (t_shellenv_ptr == NULL)
	{
		perror("main: mk_shell_env failed");
		exit(1);
	}
	t_shellenv_ptr->env_list = env_to_list(t_shellenv_ptr->envp);
	return (t_shellenv_ptr);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		**split_token;
	t_job		*job_head;
	t_shell_env	*t_shellenv_ptr;

	init_gstate();
	(void)argc;
	(void)argv;
	t_shellenv_ptr = init_tshellenv(envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline_seq(t_shellenv_ptr);
		add_history(input);
		split_token = lexer(input);
		free(input);
		if (split_token != NULL)
		{
			job_head = parse_line(split_token, t_shellenv_ptr);
			if (t_shellenv_ptr->exit_status != 0)
			{
				free_all_job(job_head);
				// free_all_token(split_token);
				continue ;
			}
			expander(job_head, t_shellenv_ptr);
			// dump_jobs(job_head);
			ft_exec(job_head, t_shellenv_ptr);
			// 後処理
			free_all_job(job_head);
			// free_all_token(split_token);
		}
	}
}
