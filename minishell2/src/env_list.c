/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:10:32 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/17 16:12:03 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
	char *key;          // 環境変数のキー
	char *value;        // 環境変数の値
	struct s_env *next; // 次のノード
}		t_env;

t_env	*create_node(char *env_str)
{
	t_env	*node;
	char	*delimiter;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	// "KEY=VALUE"を分割
	delimiter = ft_strchr(env_str, '=');
	if (!delimiter)
	{
		free(node);
		return (NULL);
	}
	key_len = delimiter - env_str;
	node->key = ft_strndup(env_str, key_len); // KEY部分をコピー
	node->value = ft_strdup(delimiter + 1);   // VALUE部分をコピー
	node->next = NULL;
	return (node);
}

t_env	*env_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i] != NULL)
	{
		new_node = create_node(envp[i]);
		if (new_node) // エラー時以外の処理
		{
			if (!head)
			{
				head = new_node;
				tail = head;
			}
			else
			{
				tail->next = new_node;
				tail = new_node;
			}
		}
		i++;
	}
	return (head);
}

void	print_env_list(t_env *head)
{
	while (head)
	{
		printf("KEY: %s, VALUE: %s\n", head->key, head->value);
		head = head->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env_list;

// 	// 環境変数を連結リストに変換
// 	env_list = env_to_list(envp);
// 	// 連結リストを出力
// 	print_env_list(env_list);
// 	return (0);
// }
