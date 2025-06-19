/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 20:45:26 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(t_shell_env *shell_env, int status)
{
	if (!shell_env)
		return ;
	shell_env->exit_status = status;
}

// HEREDOCを事前処理する関数
void	process_heredocs(t_pipeline *pipeline, t_shell_env *shell_env)
{
	t_pipeline	*current;
	t_redirect	*redir;
	int			tmp_fd;
	char		*line;
	char		tmp_filename[256];
	static int	heredoc_count = 0;

	current = pipeline;
	while (current)
	{
		redir = current->cmd->redir;
		while (redir)
		{
			if (redir->type == TYPE_REDIRECT_HEREDOC)
			{
				// HEREDOCの区切り文字チェック
				if (!redir->filename || strlen(redir->filename) == 0)
				{
					write(STDERR_FILENO,
						"minishell: syntax error near unexpected token `newline'\n",
						59);
					update_exit_status(shell_env, 2); // シンタックスエラー
					return ;                           // 即時終了
				}
				// 一時ファイル名を生成
				snprintf(tmp_filename, sizeof(tmp_filename),
					"/tmp/minishell_heredoc_%d_%d", getpid(), heredoc_count++);
				// 一時ファイルを作成
				tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
				if (tmp_fd < 0)
				{
					perror("minishell: open");
					update_exit_status(shell_env, 1); // ファイル作成エラー
					return ;                           // 即時終了
				}
				// HEREDOCの入力処理
				write(STDOUT_FILENO, "Here-doc (end with '", 20);
				write(STDOUT_FILENO, redir->filename, strlen(redir->filename));
				write(STDOUT_FILENO, "'):\n", 4);
				while (1)
				{
					line = readline("> ");
					if (!line) // EOFやシグナルで中断
					{
						update_exit_status(shell_env, 130); // Ctrl+Cのような中断
						close(tmp_fd);
						unlink(tmp_filename); // 作成済みファイルを削除
						return ;
					}
					if (strcmp(line, redir->filename) == 0) // 終了文字列
					{
						free(line);
						break ;
					}
					write(tmp_fd, line, strlen(line));
					write(tmp_fd, "\n", 1); // 改行を追加
					free(line);
				}
				close(tmp_fd);
				// 元のfilenameを保存してから一時ファイル名に置き換え
				free(redir->filename);
				redir->filename = strdup(tmp_filename);
				if (!redir->filename)
				{
					write(STDERR_FILENO, "minishell: strdup: Out of memory\n",
						33);
					unlink(tmp_filename);             // 作成したファイルを削除
					update_exit_status(shell_env, 1); // メモリ不足エラー
					return ;
				}
				// typeを通常のファイル入力に変更
				redir->type = TYPE_REDIRECT_IN;
			}
			redir = redir->next;
		}
		current = current->next;
	}
	// 正常終了
	update_exit_status(shell_env, 0);
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

// リダイレクト処理関数
void	handle_redirects(t_redirect *redir, t_shell_env *shell_env)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				update_exit_status(shell_env, 1); // ファイルオープン失敗
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == TYPE_REDIRECT_OUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				update_exit_status(shell_env, 1); // ファイルオープン失敗
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == TYPE_REDIRECT_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				update_exit_status(shell_env, 1); // ファイルオープン失敗
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
		{
			fprintf(stderr, "Unknown redirect type\n");
			update_exit_status(shell_env, 1); // 未知のリダイレクトタイプ
			return ;
		}
		redir = redir->next;
	}
	update_exit_status(shell_env, 0); // リダイレクト成功
}

void	execute_builtin(char **argv, t_shell_env *shell_env)
{
	// print_env_list(shell_env->env_list);
	if (strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, shell_env);
	else if (strcmp(argv[0], "echo") == 0)
		builtin_echo(argv);
	else if (strcmp(argv[0], "env") == 0)
		builtin_env(argv, &shell_env, shell_env);
	else if (strcmp(argv[0], "exit") == 0)
		builtin_exit(argv);
	else if (strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell_env);
	else if (strcmp(argv[0], "pwd") == 0)
		builtin_pwd(&shell_env->env_list, shell_env);
	else if (strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, &shell_env->env_list, shell_env);
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

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

static char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(path, "/");
	if (!part_path)
		error();
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	if (!full_path)
		error();
	return (full_path);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	if (!access(cmd, X_OK))
		return (cmd);
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error();
	i = 0;
	while (paths[i])
	{
		path = join_path_and_cmd(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (free_paths(paths), path);
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char	**env_list_to_envp(t_env *env_list)
{
	t_env	*current;
	int		count;
	char	**envp;
	int		i;
	size_t	key_len;
	size_t	value_len;

	current = env_list;
	count = 0;
	// リストのサイズを計算
	while (current)
	{
		count++;
		current = current->next;
	}
	// 配列を確保 (+1 は NULL 終端のため)
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	// リストを配列に変換
	current = env_list;
	i = 0;
	while (current)
	{
		// "KEY=VALUE" の形式で文字列を作成
		key_len = strlen(current->key);
		value_len = strlen(current->value);
		envp[i] = (char *)malloc(key_len + value_len + 2); // '=' + '\0'
		if (!envp[i])
		{
			// メモリ解放
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		sprintf(envp[i], "%s=%s", current->key, current->value);
		i++;
		current = current->next;
	}
	envp[i] = NULL; // 配列の終端を設定
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	execute(char **av, t_shell_env *shell_env)
{
	int		i;
	char	*path;
	char	**envp;

	i = 0;
	envp = env_list_to_envp(shell_env->env_list);
	if (!envp)
	{
		update_exit_status(shell_env, 1); // メモリ不足の可能性
		error();
	}
	path = find_path(av[0], envp);
	if (!path)
	{
		update_exit_status(shell_env, 127); // コマンドが見つからない
		fprintf(stderr, "minishell: %s: command not found\n", av[0]);
		while (av[i])
			free(av[i++]);
		free(av);
		free_envp(envp);
		exit(shell_env->exit_status); // 設定したステータスを反映
	}
	if (execve(path, av, envp) == -1)
	{
		update_exit_status(shell_env, 126); // 実行失敗
		perror("minishell");
		free(path); // パスの解放を追加
		free_envp(envp);
		exit(shell_env->exit_status); // 設定したステータスを反映
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
	// 前のパイプの読み取り側を標準入力にリダイレクト
	if (prev_pipe[0] != -1)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		prev_pipe[0] = -1;
	}
	// 次のパイプがある場合、パイプを作成し標準出力にリダイレクト
	if (pipeline->next)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			update_exit_status(shell_env, 1); // パイプ作成失敗
			return ;
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	// リダイレクト処理とビルトイン実行
	handle_redirects(pipeline->cmd->redir, shell_env);
	// ビルトイン実行中に発生する可能性があるエラーをキャッチ
	// エラー時には`exit_status`を設定する
	if (pipeline->cmd->argv && pipeline->cmd->argv[0])
	{
		execute_builtin(pipeline->cmd->argv, shell_env);
		exit_status = shell_env->exit_status; // 実行後のステータスを反映
	}
	else
	{
		write(STDERR_FILENO, "minishell: command not found\n", 29);
		exit_status = 127; // コマンドが見つからない場合
	}
	// 標準入出力を元に戻す
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	// 次のパイプラインのために読み取り側を保存
	if (pipeline->next)
		prev_pipe[0] = pipe_fd[0];
	// 終了ステータスを更新
	update_exit_status(shell_env, exit_status);
}

void	handle_external(t_pipeline *pipeline, t_shell_env *shell_env,
		int prev_pipe[2], int pipe_fd[2])
{
	pid_t	pid;
	int		status;

	// 次のコマンドがある場合のみパイプを作成
	if (pipeline->next && pipe(pipe_fd) < 0)
	{
		perror("pipe");
		update_exit_status(shell_env, 1); // パイプ作成失敗
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		update_exit_status(shell_env, 1); // フォーク失敗
		return ;
	}
	if (pid == 0)
	{
		// 子プロセス：パイプ設定と外部コマンド実行
		if (prev_pipe[0] != -1)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
		}
		if (pipeline->next)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]); // 子プロセスでは読み取り側は不要
		}
		// リダイレクト処理（heredocを含む）
		handle_redirects(pipeline->cmd->redir, shell_env);
		execute(pipeline->cmd->argv, shell_env);
		perror("execute");
		exit(EXIT_FAILURE); // 子プロセス終了
	}
	// 親プロセス：パイプとプロセス管理
	if (prev_pipe[0] != -1)
		close(prev_pipe[0]);
	if (pipeline->next)
	{
		close(pipe_fd[1]); // 親プロセスでは書き込み側は不要
		prev_pipe[0] = pipe_fd[0];
	}
	// 子プロセスの終了ステータスを取得
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		update_exit_status(shell_env, 1); // 子プロセス管理失敗
		return ;
	}
	// 終了ステータスを更新
	if (WIFEXITED(status)) // 子プロセスが正常終了した場合
		update_exit_status(shell_env, WEXITSTATUS(status));
	else if (WIFSIGNALED(status)) // 子プロセスがシグナルで終了した場合
		update_exit_status(shell_env, 128 + WTERMSIG(status));
}

void	ft_exec(t_job *job_head, t_shell_env *shell_env)
{
	t_job		*current_job;
	t_pipeline	*current_pipeline;
	int			pipe_fd[2];
	pid_t		pid;
	int			status;

	int prev_pipe[2] = {-1, -1}; // 前のパイプ用
	current_job = job_head;
	while (current_job)
	{
		current_pipeline = current_job->pipeline;
		prev_pipe[0] = -1; // 各ジョブの開始時にリセット
		prev_pipe[1] = -1;
		// パイプライン実行前にすべてのheredocを事前処理
		process_heredocs(current_pipeline, shell_env);
		while (current_pipeline)
		{
			if (is_builtin(current_pipeline->cmd->argv[0]))
			{
				// ビルトインコマンドの処理
				handle_builtin(current_pipeline, shell_env, prev_pipe, pipe_fd);
			}
			else
			{
				// 外部コマンドの処理
				handle_external(current_pipeline, shell_env, prev_pipe,
					pipe_fd);
			}
			current_pipeline = current_pipeline->next;
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
		// 一時ファイルをクリーンアップ
		cleanup_heredoc_files(current_job->pipeline);
		current_job = current_job->next;
	}
}
