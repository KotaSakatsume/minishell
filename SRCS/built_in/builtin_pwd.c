/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 11:41:10 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAX 4096

int	get_current_directory(char *cwd, size_t size)
{
	if (getcwd(cwd, size) == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	return (0);
}

void	update_or_add_pwd(t_env **env_list, t_shell_env *shell_env, char *cwd)
{
	t_env	*node;
	t_env	*new_node;

	node = *env_list;
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
		{
			return (free(node->value), node->value = ft_strdup(cwd),
				update_exit_status(shell_env, 0));
		}
		node = node->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Memory allocation failed");
		return (update_exit_status(shell_env, 1));
	}
	new_node->key = ft_strdup("PWD");
	new_node->value = ft_strdup(cwd);
	new_node->next = *env_list;
	*env_list = new_node;
	update_exit_status(shell_env, 0);
}

void	sync_pwd_env(t_env **env_list, t_shell_env *shell_env)
{
	char	cwd[PATH_MAX];

	if (get_current_directory(cwd, sizeof(cwd)) != 0)
	{
		update_exit_status(shell_env, 1);
		return ;
	}
	update_or_add_pwd(env_list, shell_env, cwd);
}

void	builtin_pwd(t_env **env_list, t_shell_env *shell_env)
{
	t_env	*node;

	sync_pwd_env(env_list, shell_env);
	node = *env_list;
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
		{
			printf("%s\n", node->value);
			update_exit_status(shell_env, 0);
			return ;
		}
		node = node->next;
	}
	write(2, "PWD not found in environment variables\n", 39);
	update_exit_status(shell_env, 1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env_list;

// 	// 環境変数を連結リストに変換
// 	env_list = env_to_list(envp);
// 	if (!env_list)
// 	{
// 		perror("Failed to initialize environment list");
// 		return (1);
// 	}
// 	// 引数解析
// 	if (ac == 2 && strcmp(av[1], "pwd") == 0)
// 	{
// 		print_pwd(&env_list);
// 	}
// 	else
// 	{
// 		fprintf(stderr, "Usage: %s pwd\n", av[0]);
// 	}
// 	// 環境変数リストを解放
// 	free_env_list(env_list);
// 	return (0);
// }
