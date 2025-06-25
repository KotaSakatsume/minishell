/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 06:46:11 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/24 01:48:26 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fx_extend_to_all_pipeline(t_job *job_head, void (*extend)(t_pipeline *))
{
	t_job *job_ptr;
	job_ptr = job_head;

	t_pipeline *pipeline_ptr;

	while (job_ptr != NULL)
	{
		pipeline_ptr = job_ptr->pipeline;
		while (pipeline_ptr != NULL)
		{
			extend(pipeline_ptr);
			pipeline_ptr = pipeline_ptr->next;
		}
		job_ptr = job_ptr->next;
	}
}


void fx_extend_to_all_pipeline_with_env(t_job *job_head, t_shell_env *t_shellenv_ptr ,void (*extend)(t_pipeline *,t_shell_env *))
{
	t_job *job_ptr;
	job_ptr = job_head;

	t_pipeline *pipeline_ptr;

	while (job_ptr != NULL)
	{
		pipeline_ptr = job_ptr->pipeline;
		while (pipeline_ptr != NULL)
		{
			extend(pipeline_ptr,t_shellenv_ptr);
			pipeline_ptr = pipeline_ptr->next;
		}
		job_ptr = job_ptr->next;
	}
}

t_token *mk_empty_token()
{
	t_token *t_token_node;
	t_token_node = malloc(sizeof(t_token));
	if (t_token_node == NULL)
	{
		perror("mk_t_token : malloc");
		return (NULL);
	}
	initialize_t_token(t_token_node);
	return (t_token_node);
}
