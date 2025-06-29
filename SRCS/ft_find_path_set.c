/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:51:33 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_char;
	const char	*src_char;

	if (!dest || !src)
		return (NULL);
	dest_char = (char *)dest;
	src_char = (const char *)src;
	i = 0;
	while (i < n)
	{
		dest_char[i] = src_char[i];
		i++;
	}
	return (dest);
}

char	*create_env_entry(char *key, char *value)
{
	size_t	key_len;
	size_t	value_len;
	char	*env_entry;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	env_entry = (char *)malloc(key_len + value_len + 2);
	if (!env_entry)
		return (NULL);
	ft_memcpy(env_entry, key, key_len);
	env_entry[key_len] = '=';
	ft_memcpy(env_entry + key_len + 1, value, value_len);
	env_entry[key_len + value_len + 1] = '\0';
	return (env_entry);
}

void	update_exit_status(t_shell_env *shell_env, int status)
{
	if (!shell_env)
		return ;
	shell_env->exit_status = status;
}

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
