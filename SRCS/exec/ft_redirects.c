/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 11:38:28 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input_redirect(const char *filename, t_shell_env *shell_env)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		update_exit_status(shell_env, 1);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	process_output_redirect(const char *filename, t_shell_env *shell_env,
		int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		update_exit_status(shell_env, 1);
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
			update_exit_status(shell_env, 1);
			exit(1);
		}
		redir = redir->next;
	}
	update_exit_status(shell_env, 0);
}
