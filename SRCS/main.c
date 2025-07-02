/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:19:08 by mkuida            #+#    #+#             */
/*   Updated: 2025/07/02 11:13:35 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigatm;

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

static void	loop_initialize(t_shell_env *t_shellenv_ptr)
{
	set_signal_for_readline();
	if(t_shellenv_ptr->exit_status == 2 || t_shellenv_ptr->exit_status == 3)
		t_shellenv_ptr->exit_status = 1;
	t_shellenv_ptr->exit_status_now = t_shellenv_ptr->exit_status;
}

static void	minishell_main_loop(t_shell_env *t_shellenv_ptr)
{
	char	*input;
	t_token	**split_token;
	t_job	*job_head;

	loop_initialize(t_shellenv_ptr);
	input = readline_seq(t_shellenv_ptr);
	set_signal_default();
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
	set_signal_default();
	t_shellenv_ptr = init_tshellenv(envp);
	while (1)
	{
		if (g_sigatm == SIGINT)
		{
			write(1, "\n", 1);
			g_sigatm = 0;
		}
		minishell_main_loop(t_shellenv_ptr);
	}
	return (1);
}
