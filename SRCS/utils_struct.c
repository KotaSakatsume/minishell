/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 17:40:00 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token_cont(t_token **dest)
{
	t_token	*next;
	int		i;

	next = *dest;
	i = 0;
	while (next != NULL)
	{
		i++;
		next = next->next;
	}
	return (i);
}

void	free_alltoken_ptr(t_token *dest)
{
	t_token	*now_token;
	t_token	*next_token;

	now_token = dest;
	while (now_token != NULL)
	{
		next_token = now_token->next;
		free_token(now_token);
		now_token = next_token;
	}
}

void	update_pipeline_node(t_pipeline **head, t_pipeline **tail,
		t_pipeline *node)
{
	if (*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}

void	update_job_list(t_job **head, t_job **tail, t_job *job_ptr)
{
	if (*head == NULL)
	{
		*tail = job_ptr;
		*head = *tail;
	}
	else
	{
		(*tail)->next = job_ptr;
		*tail = job_ptr;
	}
}
