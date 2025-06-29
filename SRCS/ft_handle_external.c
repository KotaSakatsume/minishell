/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 11:33:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(t_pipeline *pipeline, int pipe_fd[2], t_shell_env *shell_env)
{
	if (pipeline->next && pipe(pipe_fd) < 0)
	{
		perror("pipe");
		update_exit_status(shell_env, 1);
	}
}

void	fork_and_execute(t_pipeline *pipeline, t_shell_env *shell_env,
		int prev_pipe[2], int pipe_fd[2])
{
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}
	if (pipeline->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	handle_redirects(pipeline->cmd->redir, shell_env);
	execute(pipeline->cmd->argv, shell_env);
	perror("execute");
	exit(EXIT_FAILURE);
}

void	handle_exit_status(t_shell_env *shell_env, int status)
{
	if (WIFEXITED(status))
		update_exit_status(shell_env, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		update_exit_status(shell_env, 128 + WTERMSIG(status));
}

void	parent_process_cleanup(t_pipeline *pipeline, int prev_pipe[2],
		int pipe_fd[2])
{
	if (prev_pipe[0] != -1)
		close(prev_pipe[0]);
	if (pipeline->next)
	{
		close(pipe_fd[1]);
		prev_pipe[0] = pipe_fd[0];
	}
}

void	handle_external(t_pipeline *pipeline, t_shell_env *shell_env,
		int prev_pipe[2], int pipe_fd[2])
{
	pid_t	pid;
	int		status;

	setup_pipe(pipeline, pipe_fd, shell_env);
	if (pipeline->next && pipe_fd[0] < 0)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		update_exit_status(shell_env, 1);
		return ;
	}
	if (pid == 0)
		fork_and_execute(pipeline, shell_env, prev_pipe, pipe_fd);
	else
	{
		parent_process_cleanup(pipeline, prev_pipe, pipe_fd);
		if (waitpid(pid, &status, 0) != -1)
			handle_exit_status(shell_env, status);
		else
			perror("waitpid");
	}
}
