/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:35:42 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(path, "/");
	if (!part_path)
		ft_error();
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	if (!full_path)
		ft_error();
	return (full_path);
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
		ft_error();
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
