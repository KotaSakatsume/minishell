/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:51 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 11:41:36 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	split_key_value(char *str, t_env *new_env_list)
{
	char	**parts;
	int		i;
	char	*tmp;

	parts = NULL;
	tmp = str;
	i = 0;
	while (*tmp)
	{
		if (*tmp == '=')
		{
			parts = ft_split(str, '=');
			if (!parts)
			{
				perror("ft_split failed");
				exit(EXIT_FAILURE);
			}
			new_env_list->key = ft_strdup(parts[0]);
			if (parts[1])
				new_env_list->value = ft_strdup(parts[1]);
			else
				new_env_list->value = ft_strdup("");
			while (parts[i])
			{
				safe_free(parts[i]);
				i++;
			}
			safe_free(parts);
		}
		tmp++;
	}
	return ;
}

int	is_valid_key(const char *key)
{
	if (!key || !((*key >= 'A' && *key <= 'Z') || (*key >= 'a' && *key <= 'z')
			|| (*key == '_')))
		return (0);
	key++;
	while (*key)
	{
		if (!((*key >= 'A' && *key <= 'Z') || (*key >= 'a' && *key <= 'z')
				|| (*key >= '0' && *key <= '9') || (*key == '_')))
			return (0);
		key++;
	}
	return (1);
}

t_env	*get_env_by_key(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_env(t_env *new_env_list, t_env **env_list, t_shell_env *shell_env)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc failed");
		update_exit_status(shell_env, 1);
		exit(EXIT_FAILURE);
	}
	new_node->key = ft_strdup(new_env_list->key);
	new_node->value = ft_strdup(new_env_list->value);
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

void	update_or_add_env(t_env *new_env_list, t_env **env_list,
		t_shell_env *shell_env)
{
	t_env	*existing_node;

	existing_node = get_env_by_key(new_env_list->key, *env_list);
	if (existing_node)
	{
		safe_free(existing_node->value);
		existing_node->value = ft_strdup(new_env_list->value);
	}
	else
		add_env(new_env_list, env_list, shell_env);
}

static void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	safe_free(node->key);
	safe_free(node->value);
	safe_free(node);
}

void	main_export(char *str, t_env **env_list, t_shell_env *shell_env)
{
	t_env	*new_env_list;

	new_env_list = malloc(sizeof(t_env));
	if (!new_env_list)
	{
		perror("malloc failed");
		update_exit_status(shell_env, 1);
		exit(EXIT_FAILURE);
	}
	new_env_list->key = NULL;
	new_env_list->value = NULL;
	new_env_list->next = NULL;
	if (str[0] != '=')
		split_key_value(str, new_env_list);
	if (!is_valid_key(new_env_list->key))
	{
		if (new_env_list->key != NULL || str[0] == '=')
			write(2, "Error: Invalid key\n", 19);
		free_env_node(new_env_list);
		return (update_exit_status(shell_env, 1));
	}
	update_or_add_env(new_env_list, env_list, shell_env);
	free_env_node(new_env_list);
	update_exit_status(shell_env, 0);
}

void	builtin_export(char **av, t_shell_env *shell_env)
{
	if (!av[1])
	{
		builtin_env(av, &shell_env, shell_env);
		update_exit_status(shell_env, 0);
		return ;
	}
	main_export(av[1], &shell_env->env_list, shell_env);
}
