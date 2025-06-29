/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 13:40:51 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// char	*create_env_entry(char *key, char *value)
// {
// 	size_t	key_len;
// 	size_t	value_len;
// 	char	*env_entry;

// 	key_len = ft_strlen(key);
// 	value_len = ft_strlen(value);
// 	env_entry = (char *)malloc(key_len + value_len + 2);
// 	if (env_entry)
// 		sprintf(env_entry, "%s=%s", key, value);
// 	return (env_entry);
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
