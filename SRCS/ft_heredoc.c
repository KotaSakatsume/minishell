/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 11:35:31 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_heredoc_delimiter(char *delimiter, t_shell_env *shell_env)
{
	if (!delimiter || ft_strlen(delimiter) == 0)
	{
		write(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		update_exit_status(shell_env, 2);
		exit(2);
	}
}

int	create_temporary_file(char *tmp_filename, size_t size, int heredoc_count)
{
	snprintf(tmp_filename, size, "/tmp/minishell_heredoc_%d_%d", getpid(),
		heredoc_count);
	return (open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

void	process_heredoc_input(int tmp_fd, char *delimiter,
		t_shell_env *shell_env)
{
	char	*line;

	write(STDOUT_FILENO, "Here-doc (end with '", 20);
	write(STDOUT_FILENO, delimiter, strlen(delimiter));
	write(STDOUT_FILENO, "'):\n", 4);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			update_exit_status(shell_env, 130);
			close(tmp_fd);
			exit(130);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
}

void	replace_heredoc_with_tempfile(t_redirect *redir, char *tmp_filename,
		t_shell_env *shell_env)
{
	free(redir->filename);
	redir->filename = ft_strdup(tmp_filename);
	if (!redir->filename)
	{
		write(STDERR_FILENO, "minishell: strdup: Out of memory\n", 33);
		unlink(tmp_filename);
		update_exit_status(shell_env, 1);
		exit(1);
	}
	redir->type = TYPE_REDIRECT_IN;
}

void	process_single_heredoc(t_redirect *redir, int heredoc_count,
		t_shell_env *shell_env)
{
	char	tmp_filename[256];
	int		tmp_fd;

	validate_heredoc_delimiter(redir->filename, shell_env);
	tmp_fd = create_temporary_file(tmp_filename, sizeof(tmp_filename),
			heredoc_count);
	if (tmp_fd < 0)
	{
		perror("minishell: open");
		update_exit_status(shell_env, 1);
		exit(1);
	}
	process_heredoc_input(tmp_fd, redir->filename, shell_env);
	replace_heredoc_with_tempfile(redir, tmp_filename, shell_env);
}

void	process_heredocs(t_pipeline *pipeline, t_shell_env *shell_env)
{
	t_pipeline	*current;
	t_redirect	*redir;
	static int	heredoc_count = 0;

	current = pipeline;
	while (current)
	{
		redir = current->cmd->redir;
		while (redir)
		{
			if (redir->type == TYPE_REDIRECT_HEREDOC)
				process_single_heredoc(redir, heredoc_count++, shell_env);
			redir = redir->next;
		}
		current = current->next;
	}
	update_exit_status(shell_env, 0);
}
