/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:10:32 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 12:06:23 by kosakats         ###   ########.fr       */
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
		temp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = temp;
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
	delimiter = ft_strchr(env_str, '=');
	if (!delimiter)
	{
		free(node);
		return (NULL);
	}
	key_len = delimiter - env_str;
	node->key = ft_strndup(env_str, key_len);
	node->value = ft_strdup(delimiter + 1);
	node->next = NULL;
	return (node);
}

void	append_env_node(t_env **head, t_env **tail, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

t_env	*env_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_node(envp[i]);
		if (new_node)
			append_env_node(&head, &tail, new_node);
		i++;
	}
	return (head);
}
