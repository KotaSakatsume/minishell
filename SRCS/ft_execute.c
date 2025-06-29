/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:35:38 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_error(void)
// {
// 	perror("Error");
// 	exit(EXIT_FAILURE);
// }

// void	free_envp(char **envp)
// {
// 	int	i;

// 	if (!envp)
// 		return ;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// }

// void	free_paths(char **paths)
// {
// 	int	i;

// 	i = 0;
// 	while (paths[i])
// 		free(paths[i++]);
// 	free(paths);
// }

// char	*join_path_and_cmd(char *path, char *cmd)
// {
// 	char	*part_path;
// 	char	*full_path;

// 	part_path = ft_strjoin(path, "/");
// 	if (!part_path)
// 		ft_error();
// 	full_path = ft_strjoin(part_path, cmd);
// 	free(part_path);
// 	if (!full_path)
// 		ft_error();
// 	return (full_path);
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
// 		ft_error();
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

int	calculate_env_list_size(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// char	**allocate_envp_array(int count)
// {
// 	char	**envp;

// 	envp = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (envp)
// 		envp[count] = NULL;
// 	return (envp);
// }

char	*create_env_entry(char *key, char *value)
{
	size_t	key_len;
	size_t	value_len;
	char	*env_entry;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	env_entry = (char *)malloc(key_len + value_len + 2);
	if (env_entry)
		sprintf(env_entry, "%s=%s", key, value);
	return (env_entry);
}

// void	free_envp_array(char **envp, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// }

char	**env_list_to_envp(t_env *env_list)
{
	int		count;
	char	**envp;
	t_env	*current;
	int		i;

	count = calculate_env_list_size(env_list);
	envp = allocate_envp_array(count);
	if (!envp)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		envp[i] = create_env_entry(current->key, current->value);
		if (!envp[i])
		{
			free_envp_array(envp, i);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	return (envp);
}

char	*prepare_execution(char **av, t_shell_env *shell_env, char ***envp)
{
	char	*path;

	*envp = env_list_to_envp(shell_env->env_list);
	if (!(*envp))
	{
		update_exit_status(shell_env, 1);
		ft_error();
	}
	path = find_path(av[0], *envp);
	if (!path)
	{
		update_exit_status(shell_env, 127);
		write(2, "minishell: ", 11);
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": command not found\n", 20);
		exit(shell_env->exit_status);
	}
	return (path);
}

void	execute_command(char *path, char **av, char **envp,
		t_shell_env *shell_env)
{
	if (execve(path, av, envp) == -1)
	{
		update_exit_status(shell_env, 126);
		perror("minishell");
		free(path);
		free_envp(envp);
		exit(shell_env->exit_status);
	}
}

void	execute(char **av, t_shell_env *shell_env)
{
	char	*path;
	char	**envp;

	path = prepare_execution(av, shell_env, &envp);
	execute_command(path, av, envp, shell_env);
}
