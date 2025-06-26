/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:51:11 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 06:20:14 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_cmd(t_cmd *cmd_node)
{
	t_redirect	*freed_node;
	t_redirect	*next_node;
	int			i;

	i = 0;
	next_node = cmd_node->redir;
	while (next_node != NULL)
	{
		free(next_node->filename);
		freed_node = next_node;
		free(freed_node);
		next_node = next_node->next;
	}
	while (cmd_node->argv[i] != NULL)
	{
		free(cmd_node->argv[i]);
		i++;
	}
	i = 0;
	while (cmd_node->token && cmd_node->token[i] != NULL)
	{
		if (cmd_node->token[i]->value != NULL)
			free(cmd_node->token[i]->value);
		if (cmd_node->token[i]->status != NULL)
			free(cmd_node->token[i]->status);
		free(cmd_node->token[i]);
		i++;
	}
	free(cmd_node->argv);
	free(cmd_node->token);
	free(cmd_node);
}

void	free_all_pipeline(t_pipeline *pipeline_node)
{
	t_pipeline	*freed_pipeline_node;

	while (pipeline_node != NULL)
	{
		free_all_cmd(pipeline_node->cmd);
		freed_pipeline_node = pipeline_node;
		pipeline_node = pipeline_node->next;
		free(freed_pipeline_node);
	}
}

void	free_all_job(t_job *job_node)
{
	t_job	*freed_job_node;

	while (job_node != NULL)
	{
		free_all_pipeline(job_node->pipeline);
		freed_job_node = job_node;
		job_node = job_node->next;
		free(freed_job_node);
	}
}
