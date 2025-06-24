/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/20 14:23:41 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(t_shell_env *shell_env, int status)
{
	if (!shell_env)
		return ;
	shell_env->exit_status = status;
}

// 一時ファイルをクリーンアップする関数
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
			if (redir->filename && strstr(redir->filename,
					"/tmp/minishell_heredoc_"))
			{
				unlink(redir->filename); // 一時ファイルを削除
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

int	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"cd", "echo", "exit", "env", "export", "pwd",
			"unset"};
	int			i;

	i = 0;
	while (i < 7) // 配列サイズを7に修正（pwdが抜けていた）
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	process_pipeline(t_pipeline *pipeline, t_shell_env *shell_env,
		int *prev_pipe, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	while (pipeline)
	{
		if (is_builtin(pipeline->cmd->argv[0]))
			// ビルトインコマンドの処理
			handle_builtin(pipeline, shell_env, prev_pipe, pipe_fd);
		else
			// 外部コマンドの処理
			handle_external(pipeline, shell_env, prev_pipe, pipe_fd);
		pipeline = pipeline->next;
	}
	// 最後に残ったパイプをクリーンアップ
	if (prev_pipe[0] != -1)
		close(prev_pipe[0]);
	// パイプライン内のすべてのプロセスが終了するまで待機
	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
			update_exit_status(shell_env, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			update_exit_status(shell_env, 128 + WTERMSIG(status));
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
		prev_pipe[0] = -1; // 各ジョブの開始時にリセット
		prev_pipe[1] = -1;
		// パイプライン実行前にすべてのheredocを事前処理
		process_heredocs(current_pipeline, shell_env);
		// パイプラインの処理
		process_pipeline(current_pipeline, shell_env, prev_pipe, pipe_fd);
		// 一時ファイルをクリーンアップ
		cleanup_heredoc_files(current_job->pipeline);
		current_job = current_job->next;
	}
}
