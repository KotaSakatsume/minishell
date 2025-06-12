/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:51 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:52 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ヘルパー関数: メモリを安全に解放する
void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
}

// メモリ解放
// void	free_env_list(t_env *env_list)
// {
// 	t_env	*tmp;

// 	while (env_list)
// 	{
// 		tmp = env_list->next;
// 		safe_free(env_list->key);
// 		safe_free(env_list->value);
// 		safe_free(env_list);
// 		env_list = tmp;
// 	}
// }

// 文字列をキーと値に分割
void	split_key_value(const char *str, t_env *new_env_list)
{
	char	**parts;
	int		i;

	parts = NULL;
	i = 0;
	parts = ft_split(str, '=');
	if (!parts)
	{
		perror("ft_split failed");
		exit(EXIT_FAILURE);
	}
	new_env_list->key = strdup(parts[0]);
	if (parts[1])
		new_env_list->value = strdup(parts[1]);
	else
		new_env_list->value = strdup("");
	while (parts[i])
	{
		safe_free(parts[i]);
		i++;
	}
	safe_free(parts);
}

// 環境変数のキーが有効かどうか確認
int	is_valid_key(const char *key)
{
	if (!key || !((*key >= 'A' && *key <= 'Z') || (*key >= 'a' && *key <= 'z')
			|| (*key == '_')))
	{
		return (0); // 無効なキー
	}
	key++;
	while (*key)
	{
		if (!((*key >= 'A' && *key <= 'Z') || (*key >= 'a' && *key <= 'z')
				|| (*key >= '0' && *key <= '9') || (*key == '_')))
		{
			return (0); // 無効なキー
		}
		key++;
	}
	return (1); // 有効なキー
}

// リスト内でキーを検索
t_env	*get_env_by_key(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
		{
			return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

// リストを更新または追加
void	update_or_add_env(t_env *new_env_list, t_env **env_list)
{
	t_env	*existing_node;
	t_env	*new_node;
	t_env	*current;

	existing_node = get_env_by_key(new_env_list->key, *env_list);
	if (existing_node)
	{
		safe_free(existing_node->value);
		existing_node->value = strdup(new_env_list->value);
	}
	else
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		new_node->key = strdup(new_env_list->key);
		new_node->value = strdup(new_env_list->value);
		new_node->next = NULL;
		current = *env_list;
		if (!current)
			*env_list = new_node;
		else
		{
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
	}
}

// メインエクスポート処理
void	main_export(const char *str, t_env **env_list)
{
	t_env	*new_env_list;

	new_env_list = malloc(sizeof(t_env));
	if (!new_env_list)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_env_list->key = NULL;
	new_env_list->value = NULL;
	new_env_list->next = NULL;
	split_key_value(str, new_env_list);
	if (!is_valid_key(new_env_list->key))
	{
		fprintf(stderr, "Error: Invalid key '%s'\n", new_env_list->key);
		safe_free(new_env_list->key);
		safe_free(new_env_list->value);
		safe_free(new_env_list);
		return ;
	}
	update_or_add_env(new_env_list, env_list);
	safe_free(new_env_list->key);
	safe_free(new_env_list->value);
	safe_free(new_env_list);
}

// ビルトインエクスポート
void	builtin_export(char **av, t_shell_env *shell_env)
{
	if (!av[1])
	{
		builtin_env(&shell_env);
		return ;
	}
	main_export(av[1], &shell_env->env_list);
}
