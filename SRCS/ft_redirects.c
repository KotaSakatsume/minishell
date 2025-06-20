/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/20 15:20:56 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	process_heredocs(t_pipeline *pipeline, t_shell_env *shell_env)
// {
// 	t_pipeline	*current;
// 	t_redirect	*redir;
// 	int			tmp_fd;
// 	char		*line;
// 	char		tmp_filename[256];
// 	static int	heredoc_count = 0;

// 	current = pipeline;
// 	while (current)
// 	{
// 		redir = current->cmd->redir;
// 		while (redir)
// 		{
// 			if (redir->type == TYPE_REDIRECT_HEREDOC)
// 			{
// 				// HEREDOCの区切り文字チェック
// 				if (!redir->filename || strlen(redir->filename) == 0)
// 				{
// 					write(STDERR_FILENO,
// 						"minishell: syntax error near unexpected token `newline'\n",
// 						59);
// 					update_exit_status(shell_env, 2); // シンタックスエラー
// 					return ;                           // 即時終了
// 				}
// 				// 一時ファイル名を生成
// 				snprintf(tmp_filename, sizeof(tmp_filename),
// 					"/tmp/minishell_heredoc_%d_%d", getpid(), heredoc_count++);
// 				// 一時ファイルを作成
// 				tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
// 				if (tmp_fd < 0)
// 				{
// 					perror("minishell: open");
// 					update_exit_status(shell_env, 1); // ファイル作成エラー
// 					return ;                           // 即時終了
// 				}
// 				// HEREDOCの入力処理
// 				write(STDOUT_FILENO, "Here-doc (end with '", 20);
// 				write(STDOUT_FILENO, redir->filename, strlen(redir->filename));
// 				write(STDOUT_FILENO, "'):\n", 4);
// 				while (1)
// 				{
// 					line = readline("> ");
// 					if (!line) // EOFやシグナルで中断
// 					{
// 						update_exit_status(shell_env, 130); // Ctrl+Cのような中断
// 						close(tmp_fd);
// 						unlink(tmp_filename); // 作成済みファイルを削除
// 						return ;
// 					}
// 					if (strcmp(line, redir->filename) == 0) // 終了文字列
// 					{
// 						free(line);
// 						break ;
// 					}
// 					write(tmp_fd, line, strlen(line));
// 					write(tmp_fd, "\n", 1); // 改行を追加
// 					free(line);
// 				}
// 				close(tmp_fd);
// 				// 元のfilenameを保存してから一時ファイル名に置き換え
// 				free(redir->filename);
// 				redir->filename = strdup(tmp_filename);
// 				if (!redir->filename)
// 				{
// 					write(STDERR_FILENO, "minishell: strdup: Out of memory\n",
// 						33);
// 					unlink(tmp_filename);             // 作成したファイルを削除
// 					update_exit_status(shell_env, 1); // メモリ不足エラー
// 					return ;
// 				}
// 				// typeを通常のファイル入力に変更
// 				redir->type = TYPE_REDIRECT_IN;
// 			}
// 			redir = redir->next;
// 		}
// 		current = current->next;
// 	}
// 	// 正常終了
// 	update_exit_status(shell_env, 0);
// }

void	process_input_redirect(const char *filename, t_shell_env *shell_env)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		update_exit_status(shell_env, 1); // ファイルオープン失敗
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	process_output_redirect(const char *filename, t_shell_env *shell_env,
		int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror("open");
		update_exit_status(shell_env, 1); // ファイルオープン失敗
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirects(t_redirect *redir, t_shell_env *shell_env)
{
	while (redir)
	{
		if (redir->type == TYPE_REDIRECT_IN)
		{
			process_input_redirect(redir->filename, shell_env);
		}
		else if (redir->type == TYPE_REDIRECT_OUT)
		{
			process_output_redirect(redir->filename, shell_env, 0);
		}
		else if (redir->type == TYPE_REDIRECT_APPEND)
		{
			process_output_redirect(redir->filename, shell_env, 1);
		}
		else
		{
			write(STDERR_FILENO, "Unknown redirect type\n", 22);
			update_exit_status(shell_env, 1); // 未知のリダイレクトタイプ
			exit(1);
		}
		redir = redir->next;
	}
	update_exit_status(shell_env, 0); // リダイレクト成功
}
