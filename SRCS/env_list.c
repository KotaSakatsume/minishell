/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:10:32 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/23 23:23:44 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_env_list(t_env *head)
// {
// 	while (head)
// 	{
// 		printf("KEY: %s, VALUE: %s\n", head->key, head->value);
// 		head = head->next;
// 	}
// }

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head->next; // 次のノードを保持
		free(head->key);   // 現在のノードのキーを解放
		free(head->value); // 現在のノードの値を解放
		free(head);        // 現在のノード自体を解放
		head = temp;       // 次のノードに進む
	}
}

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
	// printf("\n");			// kakunin
	// print_env_list(head);	// kakunin
	// printf("\n");			// kakunin
	
	return (head);
}
