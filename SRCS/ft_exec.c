/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/07/01 19:49:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredoc_files(t_pipeline *pipeline)
{
	t_pipeline	*current;
	t_redirect	*redir;

	current = pipeline;
	while (current)
	{
		redir = current->cmd->redir;
		while (redir)
		{
			if (redir->filename && ft_strstr(redir->filename,
					"/tmp/minishell_heredoc_"))
			{
				unlink(redir->filename);
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

int	is_builtin(char *cmd)
{
	char	*builtins[7];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "exit";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	process_pipeline_commands(t_pipeline *pipeline, t_shell_env *shell_env,
		int *prev_pipe, int *pipe_fd)
{
	while (pipeline)
	{
		if (pipeline->cmd->argv != NULL)
		{
			if (is_builtin(pipeline->cmd->argv[0]))
				handle_builtin(pipeline, shell_env, prev_pipe, pipe_fd);
			else
				handle_external(pipeline, shell_env, prev_pipe, pipe_fd);
		}
		else
		{
			handle_external(pipeline, shell_env, prev_pipe, pipe_fd);
		}
		pipeline = pipeline->next;
	}
	if (prev_pipe[0] != -1)
		close(prev_pipe[0]);
}

void	wait_for_all_children(t_shell_env *shell_env)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			update_exit_status(shell_env, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			update_exit_status(shell_env, 128 + WTERMSIG(status));
		pid = wait(&status);
	}
}

void	ft_exec(t_job *job_head, t_shell_env *shell_env)
{
	t_job		*current_job;
	int			pipe_fd[2];
	int			prev_pipe[2];
	t_pipeline	*current_pipeline;

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	current_job = job_head;
	while (current_job)
	{
		current_pipeline = current_job->pipeline;
		prev_pipe[0] = -1;
		prev_pipe[1] = -1;
		process_heredocs(current_pipeline, shell_env);
		process_pipeline_commands(current_pipeline, shell_env, prev_pipe,
			pipe_fd);
		wait_for_all_children(shell_env);
		cleanup_heredoc_files(current_job->pipeline);
		current_job = current_job->next;
	}
}
