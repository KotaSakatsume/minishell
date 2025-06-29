/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:00:28 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 13:10:58 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 有効なキーを判定する関数
static int	is_valid_key_unset(char *args)
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

// static void	free_env_node(t_env *node)
// {
// 	if (!node)
// 		return ;
// 	free(node->key);
// 	free(node->value);
// 	free(node);
// }

void	delete_env_node(char *args, t_env **env_list)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*current;

	if (!env_list || !*env_list)
		return ;
	if (ft_strcmp((*env_list)->key, args) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		return (free_env_node(temp));
	}
	prev = *env_list;
	current = (*env_list)->next;
	while (current)
	{
		if (ft_strcmp(current->key, args) == 0)
		{
			prev->next = current->next;
			return (free_env_node(current));
		}
		prev = current;
		current = current->next;
	}
}

void	find_env_node(char *args, t_env **env_list)
{
	if (!env_list || !*env_list || !args)
		return ;
	while (*env_list)
	{
		if (ft_strcmp((*env_list)->key, args) == 0)
		{
			delete_env_node(args, env_list);
			return ;
		}
		env_list = &((*env_list)->next);
	}
}

int	unset_key(char *args, t_env **env_list)
{
	if (is_valid_key_unset(args) == 1)
	{
		write(2, "unset: '", 8);
		write(2, args, ft_strlen(args));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	find_env_node(args, env_list);
	return (0);
}

void	builtin_unset(char **args, t_env **env_list, t_shell_env *shell_env)
{
	int	i;
	int	error_status;

	i = 1;
	error_status = 0;
	while (args[i])
	{
		if (unset_key(args[i], env_list) != 0)
			error_status = 1;
		i++;
	}
	update_exit_status(shell_env, error_status);
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
