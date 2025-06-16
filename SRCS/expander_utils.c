/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 06:46:11 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/17 06:58:51 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fx_extend_to_all_pipeline(t_job *job_head , void *extend(t_pipeline*))
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
