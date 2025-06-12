/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:00:28 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/12 15:33:31 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 有効なキーを判定する関数
static int	is_valid_key(char *args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return (1);
	if (!((args[i] >= 'A' && args[i] <= 'Z') || (args[i] >= 'a'
				&& args[i] <= 'z') || (args[i] == '_')))
	{
		return (1);
	}
	while (args[i])
	{
		if (!((args[i] >= 'A' && args[i] <= 'Z') || (args[i] >= 'a'
					&& args[i] <= 'z') || (args[i] >= '0' && args[i] <= '9')
				|| (args[i] == '_')))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// 環境変数ノードを削除する関数
void	delete_env_node(char *args, t_env **env_list)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*current;

	if (!env_list || !*env_list)
		return ;
	// リストの先頭が削除対象の場合
	if (strcmp((*env_list)->key, args) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return ;
	}
	// リスト内のノードを探して削除
	prev = *env_list;
	current = (*env_list)->next;
	while (current)
	{
		if (strcmp(current->key, args) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// 環境変数ノードを見つけて削除する関数
void	find_env_node(char *args, t_env **env_list)
{
	if (!env_list || !*env_list || !args)
		return ;
	while (*env_list)
	{
		if (strcmp((*env_list)->key, args) == 0)
		{
			delete_env_node(args, env_list);
			return ;
		}
		env_list = &((*env_list)->next);
	}
}

// 環境変数を削除する関数
void	unset_key(char *args, t_env **env_list)
{
	if (is_valid_key(args) == 1)
		return ;
	find_env_node(args, env_list);
}

// ビルトインのunsetコマンド
void	builtin_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_key(args[i], env_list);
		i++;
	}
}

// 環境変数ノードを解放する関数
// void	free_env_node(t_env *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->key)
// 		free(node->key);
// 	if (node->value)
// 		free(node->value);
// 	free(node);
// }

// // メイン関数
// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env_list;

// 	env_list = env_to_list(envp);
// 	builtin_unset(av, ac, &env_list);
// 	print_env_list(env_list);
// 	free_env_list(env_list);
// 	return (0);
// }
