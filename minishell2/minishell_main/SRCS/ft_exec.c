/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/10 18:54:06 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

// void	error(void)
// {
// 	perror("Error");
// 	exit(EXIT_FAILURE);
// }

// static char	*join_path_and_cmd(char *path, char *cmd)
// {
// 	char	*part_path;
// 	char	*full_path;

// 	part_path = ft_strjoin(path, "/");
// 	if (!part_path)
// 		error();
// 	full_path = ft_strjoin(part_path, cmd);
// 	free(part_path);
// 	if (!full_path)
// 		error();
// 	return (full_path);
// }

// void	free_paths(char **paths)
// {
// 	int	i;

// 	i = 0;
// 	while (paths[i])
// 		free(paths[i++]);
// 	free(paths);
// }

// char	*find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	if (!access(cmd, X_OK))
// 		return (cmd);
// 	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
// 		i++;
// 	if (envp[i] == NULL)
// 		return (NULL);
// 	paths = ft_split(envp[i] + 5, ':');
// 	if (!paths)
// 		error();
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = join_path_and_cmd(paths[i], cmd);
// 		if (access(path, X_OK) == 0)
// 			return (free_paths(paths), path);
// 		free(path);
// 		i++;
// 	}
// 	free_paths(paths);
// 	return (NULL);
// }

// void	execute(char *av, char **envp)
// {
// 	char	**cmd;
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	cmd = ft_split(av, ' ');
// 	if (cmd == NULL)
// 		error();
// 	path = find_path(cmd[0], envp);
// 	if (!path)
// 	{
// 		while (cmd[i])
// 		{
// 			free(cmd[i]);
// 			i++;
// 		}
// 		free(cmd);
// 		error();
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 		error();
// }

void	print_command_list(t_job *head)
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;
	t_redirect	*redir;

	while (head)
	{
		printf("Job:\n");
		printf("  Separator: ");
		switch (head->sep)
		{
		case SEP_NONE:
			printf("None\n");
			break ;
		case SEP_SEQ:
			printf(";\n");
			break ;
		case SEP_AND:
			printf("&&\n");
			break ;
		case SEP_OR:
			printf("||\n");
			break ;
		default:
			printf("Unknown\n");
		}
		pipeline = head->pipeline;
		while (pipeline)
		{
			printf("  Pipeline:\n");
			cmd = pipeline->cmd;
			if (cmd)
			{
				printf("    Command Name: %s\n", cmd->argv[0]);
				printf("    Arguments:\n");
				for (int i = 0; i < cmd->argc; i++)
				{
					printf("      %s\n", cmd->argv[i]);
				}
				printf("    Redirections:\n");
				redir = cmd->redir;
				while (redir)
				{
					printf("      Type: ");
					switch (redir->type)
					{
					case TYPE_REDIRECT_IN:
						printf("<\n");
						break ;
					case TYPE_REDIRECT_OUT:
						printf(">\n");
						break ;
					case TYPE_REDIRECT_APPEND:
						printf(">>\n");
						break ;
					case TYPE_REDIRECT_HEREDOC:
						printf("<<\n");
						break ;
					default:
						printf("Unknown\n");
					}
					printf("      Filename: %s\n", redir->filename);
					redir = redir->next;
				}
			}
			else
			{
				printf("    (No Command in Pipeline)\n");
			}
			pipeline = pipeline->next;
		}
		head = head->next;
	}
}

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// リダイレクト処理関数
void	handle_redirects(t_redirect *redir)
{
	int	fd;

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
			write(fd, redir->filename, strlen(redir->filename)); // 仮に内容を書き込む
			lseek(fd, 0, SEEK_SET);
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
		else
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
		builtin_env(shell_env);
	else if (strcmp(argv[0], "exit") == 0)
		builtin_exit(argv);
	else if (strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell_env);
	// else if (strcmp(argv[0], "unset") == 0)
	// 	builtin_unset(argv, shell_env);
}

int	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"cd", "echo", "exit", "env", "export", "unset"};

	for (int i = 0; i < 6; i++)
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
	}
	return (0);
}

void	ft_exec(t_job *job_head, t_shell_env *shell_env)
{
	t_job		*current_job;
	t_pipeline	*current_pipeline;
	int			pipe_fd[2];
	pid_t		pid;
	int			status;

	current_job = job_head;
	while (current_job)
	{
		current_pipeline = current_job->pipeline;
		int prev_pipe[2] = {-1, -1}; // 前のパイプの読み書き用
		while (current_pipeline)
		{
			if (is_builtin(current_pipeline->cmd->argv[0]))
			{
				// `builtin` コマンドの処理
				if (prev_pipe[0] != -1) // パイプ入力がある場合は読む
				{
					dup2(prev_pipe[0], STDIN_FILENO);
					close(prev_pipe[0]);
				}
				handle_redirects(current_pipeline->cmd->redir);
				// リダイレクト処理
				execute_builtin(current_pipeline->cmd->argv, shell_env);
				// builtin 実行
				if (current_pipeline->next)
				// パイプが続く場合はエラー
				{
					fprintf(stderr,
						"Error: Builtin commands cannot output to pipe.\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				// パイプの生成
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
					handle_redirects(current_pipeline->cmd->redir); // リダイレクト処理
					execvp(current_pipeline->cmd->argv[0],
						current_pipeline->cmd->argv);
					perror("execvp");
					exit(EXIT_FAILURE);
				}
				// 親プロセス: パイプと子プロセス管理
				if (prev_pipe[0] != -1)
					close(prev_pipe[0]);
				if (current_pipeline->next)
					close(pipe_fd[1]);
				prev_pipe[0] = pipe_fd[0];
			}
			current_pipeline = current_pipeline->next;
		}
		// 子プロセス終了待機
		while (wait(&status) > 0)
			;
		current_job = current_job->next;
	}
}

// void	ft_exec(t_job *job_head, t_shell_env *shell_env)
// {
// 	print_command_list(job_head);
// 	// execute();
// }
