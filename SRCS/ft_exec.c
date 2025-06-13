/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/13 16:17:30 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// リダイレクト処理関数
void	handle_redirects(t_redirect *redir)
{
	int		fd;
	int		heredoc_fd;
	char	*line;

	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == TYPE_REDIRECT_OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TYPE_REDIRECT_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == TYPE_REDIRECT_HEREDOC)
		{
			// HEREDOC処理の実装
			fd = open("/tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			printf("Here-doc (end with '%s'):\n", redir->filename);
			while (1)
			{
				line = readline("> ");
				if (!line || strcmp(line, redir->filename) == 0)
				{
					free(line);
					break ;
				}
				dprintf(fd, "%s\n", line); // 内容を書き込む
				free(line);
			}
			close(fd);
			// 読み込み用に開き直す
			heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
			if (heredoc_fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		else
		{
			fprintf(stderr, "Unknown redirect type\n");
			exit(EXIT_FAILURE);
		}
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		// 標準入出力をリダイレクト
		if (redir->type == TYPE_REDIRECT_IN)
			dup2(fd, STDIN_FILENO);
		else if (redir->type == TYPE_REDIRECT_OUT
			|| redir->type == TYPE_REDIRECT_APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

void	execute_builtin(char **argv, t_shell_env *shell_env)
{
	// print_env_list(shell_env->env_list);
	if (strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, shell_env);
	else if (strcmp(argv[0], "echo") == 0)
		builtin_echo(argv);
	else if (strcmp(argv[0], "env") == 0)
		builtin_env(&shell_env);
	else if (strcmp(argv[0], "exit") == 0)
		builtin_exit(argv);
	else if (strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell_env);
	else if (strcmp(argv[0], "pwd") == 0)
		builtin_pwd(&shell_env->env_list);
	else if (strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, &shell_env->env_list);
}

int	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"cd", "echo", "exit", "env", "export", "unset"};
	int			i;

	i = 0;
	while (i < 6)
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

void	execute(char **av, t_env *env_list)
{
	int		i;
	char	*path;
	char	**envp;

	// char	**cmd;
	i = 0;
	// cmd = ft_split(av, ' ');
	// if (cmd == NULL)
	// 	error();
	// t_env -> char **envp に変換
	envp = env_list_to_envp(env_list);
	if (!envp)
		error();
	path = find_path(av[0], envp);
	if (!path)
	{
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
		error();
	}
	if (execve(path, av, envp) == -1)
		error();
}

void	ft_exec(t_job *job_head, t_shell_env *shell_env)
{
	t_job		*current_job;
	t_pipeline	*current_pipeline;
	int			pipe_fd[2];
	pid_t		pid;
	int			status;
	int			saved_stdout;
	int			saved_stdin;

	int prev_pipe[2] = {-1, -1}; // 前のパイプ用
	current_job = job_head;
	while (current_job)
	{
		current_pipeline = current_job->pipeline;
		while (current_pipeline)
		{
			if (is_builtin(current_pipeline->cmd->argv[0]))
			{
				// ビルトインコマンドの処理
				saved_stdout = dup(STDOUT_FILENO);
				saved_stdin = dup(STDIN_FILENO);
				if (prev_pipe[0] != -1)
				{
					dup2(prev_pipe[0], STDIN_FILENO);
					close(prev_pipe[0]);
					prev_pipe[0] = -1;
				}
				if (current_pipeline->next)
				{
					if (pipe(pipe_fd) < 0)
					{
						perror("pipe");
						exit(EXIT_FAILURE);
					}
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[1]);
				}
				handle_redirects(current_pipeline->cmd->redir);
				execute_builtin(current_pipeline->cmd->argv, shell_env);
				// 標準入出力を元に戻す
				dup2(saved_stdout, STDOUT_FILENO);
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdout);
				close(saved_stdin);
				if (current_pipeline->next)
					prev_pipe[0] = pipe_fd[0];
			}
			else
			{
				// 外部コマンドの処理
				if (current_pipeline->next && pipe(pipe_fd) < 0)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
				pid = fork();
				if (pid < 0)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}
				if (pid == 0) // 子プロセス
				{
					if (prev_pipe[0] != -1)
					{
						dup2(prev_pipe[0], STDIN_FILENO);
						close(prev_pipe[0]);
					}
					if (current_pipeline->next)
					{
						dup2(pipe_fd[1], STDOUT_FILENO);
						close(pipe_fd[1]);
					}
					handle_redirects(current_pipeline->cmd->redir);
					// execvp(current_pipeline->cmd->argv[0],
					// 	current_pipeline->cmd->argv);
					execute(current_pipeline->cmd->argv, shell_env->env_list);
					perror("execvp");
					exit(EXIT_FAILURE);
				}
				// 親プロセス: パイプと子プロセスの管理
				if (prev_pipe[0] != -1)
					close(prev_pipe[0]);
				if (current_pipeline->next)
					close(pipe_fd[1]);
				prev_pipe[0] = pipe_fd[0];
			}
			current_pipeline = current_pipeline->next;
		}
		// パイプライン内のすべてのプロセスが終了するまで待機
		while (wait(&status) > 0)
			;
		current_job = current_job->next;
	}
}
