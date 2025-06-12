/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/10 11:43:37 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAX 4096

void	sync_pwd_env(t_env **env_list)
{
	char	cwd[PATH_MAX];
	t_env	*node;
	t_env	*new_node;

	node = *env_list;
	// 現在のディレクトリを取得
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd failed");
		return ;
	}
	while (node)
	{
		// PWDが見つかった場合、値を更新
		if (strcmp(node->key, "PWD") == 0)
		{
			free(node->value);
			node->value = strdup(cwd);
			return ;
		}
		node = node->next;
	}
	// PWDが見つからなかった場合、新しいノードを追加
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Memory allocation failed");
		return ;
	}
	new_node->key = strdup("PWD");
	new_node->value = strdup(cwd);
	new_node->next = *env_list;
	*env_list = new_node;
}

void	builtin_pwd(t_env **env_list)
{
	t_env	*node;

	sync_pwd_env(env_list);
	// 環境変数リストからPWDを取得して出力
	node = *env_list;
	while (node)
	{
		if (strcmp(node->key, "PWD") == 0)
		{
			printf("%s\n", node->value);
			return ;
		}
		node = node->next;
	}
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
