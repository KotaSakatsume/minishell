/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:16:58 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/15 16:41:26 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"

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

void	execute(t_token *token, t_shell_env *shell_env)
{
	char	*path;
	char	*argv[2];

	path = find_path(token->value, shell_env->envp);
	if (!path)
		error();
	argv[0] = token->value;
	argv[1] = NULL;
	if (execve(path, argv, shell_env->envp) == -1)
		error();
}

void	execution_minishell(t_token *head, t_shell_env *shell_env)
{
	t_command	*cmd_head;

	// cmd_head = parse_tokens_to_commands(head);
	cmd_head = parse_tokens_to_commands(head);
	print_command_info(cmd_head); // 可視化用出力
	execute(head, shell_env);
}
