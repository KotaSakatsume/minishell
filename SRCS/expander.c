/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/05 16:15:37 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	expander(t_job *job_head)
{
	// expand_doller(job_head);
	delete_quote(job_head);
	combine_nospace_token(job_head);
	exchange_token_to_char(job_head);
}

void	delete_quote(t_job *job_head)
{
	t_job *job_ptr;
	job_ptr = job_head;

	while(job_ptr != NULL)
	{
		delete_quote_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void delete_doller_pipeline(t_job *job_ptr)	
{
	t_pipeline *pipeline_ptr;
	pipeline_ptr = job_ptr->pipeline;
	while(pipeline_ptr != NULL)
	{
		delete_quote_cmd(pipeline_ptr);
		pipeline_ptr = pipeline_ptr->next;
	}
}

void delete_quote_cmd(t_pipeline *pipeline_ptr)
{
	t_cmd *cmd_ptr;
	cmd_ptr = pipeline_ptr->cmd;
	while(cmd_ptr != NULL)
	{
		set_token_remove_quote(cmd_ptr);
		cmd_ptr++;
	}
}
