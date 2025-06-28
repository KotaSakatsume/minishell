/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:51:11 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 11:48:01 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_red(t_redirect *redirect_node)
{
	t_redirect	*now_node;
	t_redirect	*old_node;

	now_node = redirect_node;
	while (now_node != NULL)
	{
		old_node = now_node;
		now_node = now_node->next;
		free(old_node->filename);
		free(old_node);
	}
}

void	free_all_cmd(t_cmd *cmd_node)
{
	int	i;

	if (!cmd_node)
		return ;
	free_all_red(cmd_node->redir); // 引数をcmd_node->redirに修正？ (元のままだと危険)
	if (cmd_node->argv)
	{
		i = 0;
		while (cmd_node->argv[i] != NULL)
		{
			free(cmd_node->argv[i]);
			i++;
		}
		free(cmd_node->argv);
	}
	if (cmd_node->token)
	{
		i = 0;
		while (cmd_node->token[i] != NULL)
		{
			if (cmd_node->token[i]->value != NULL)
				free(cmd_node->token[i]->value);
			if (cmd_node->token[i]->status != NULL)
				free(cmd_node->token[i]->status);
			free(cmd_node->token[i]);
			i++;
		}
		free(cmd_node->token);
	}
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
