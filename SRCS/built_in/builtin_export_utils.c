/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:00:28 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 13:09:34 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		safe_free(arr[i]);
		i++;
	}
	safe_free(arr);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	safe_free(node->key);
	safe_free(node->value);
	safe_free(node);
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
