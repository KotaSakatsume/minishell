/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 11:33:04 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(char **argv, t_shell_env *shell_env)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, shell_env);
	else if (ft_strcmp(argv[0], "echo") == 0)
		builtin_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		builtin_env(argv, &shell_env, shell_env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell_env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		builtin_pwd(&shell_env->env_list, shell_env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, &shell_env->env_list, shell_env);
}

void	setup_pipes_and_redirects(t_pipeline *pipeline, t_shell_env *shell_env,
		int prev_pipe[2], int pipe_fd[2])
{
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		prev_pipe[0] = -1;
	}
	if (pipeline->next)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			update_exit_status(shell_env, 1);
			return ;
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	handle_redirects(pipeline->cmd->redir, shell_env);
}

void	execute_builtin_command(t_pipeline *pipeline, t_shell_env *shell_env,
		int *exit_status)
{
	if (pipeline->cmd->argv && pipeline->cmd->argv[0])
	{
		execute_builtin(pipeline->cmd->argv, shell_env);
		*exit_status = shell_env->exit_status;
	}
	else
	{
		write(STDERR_FILENO, "minishell: command not found\n", 29);
		*exit_status = 127;
	}
}

void	handle_builtin(t_pipeline *pipeline, t_shell_env *shell_env,
		int prev_pipe[2], int pipe_fd[2])
{
	int	saved_stdout;
	int	saved_stdin;
	int	exit_status;

	exit_status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	setup_pipes_and_redirects(pipeline, shell_env, prev_pipe, pipe_fd);
	execute_builtin_command(pipeline, shell_env, &exit_status);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	if (pipeline->next)
		prev_pipe[0] = pipe_fd[0];
	update_exit_status(shell_env, exit_status);
}
