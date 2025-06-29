/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:08 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 17:10:31 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_state		g_state;

void	handle_sigint(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
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
		perror("sigaction_int");
		exit(1);
	}
	g_state.sa_quit.sa_flags = 0;
	g_state.sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&g_state.sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &(g_state.sa_quit), NULL) == -1)
	{
		perror("sigaction_quit");
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
	t_shellenv_ptr->exit_status = 0;
	t_shellenv_ptr->exit_status_now = 0;
	return (t_shellenv_ptr);
}

static void	minishell_main_loop(t_shell_env *t_shellenv_ptr)
{
	char	*input;
	t_token	**split_token;
	t_job	*job_head;

	t_shellenv_ptr->exit_status = 0;
	t_shellenv_ptr->exit_status_now = t_shellenv_ptr->exit_status;
	input = readline_seq(t_shellenv_ptr);
	add_history(input);
	split_token = lexer(input);
	free(input);
	if (split_token != NULL)
	{
		job_head = parse_line(split_token, t_shellenv_ptr);
		if (t_shellenv_ptr->exit_status != 3)
			free_conjunc_token(split_token);
		if (t_shellenv_ptr->exit_status == 2
			|| t_shellenv_ptr->exit_status == 3)
		{
			free_all_job(job_head);
			return ;
		}
		expander(job_head, t_shellenv_ptr);
		ft_exec(job_head, t_shellenv_ptr);
		free_all_job(job_head);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	*t_shellenv_ptr;

	(void)argc;
	(void)argv;
	init_gstate();
	t_shellenv_ptr = init_tshellenv(envp);
	while (1)
		minishell_main_loop(t_shellenv_ptr);
	return (1);
}
