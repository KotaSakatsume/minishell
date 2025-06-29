/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:51:11 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 10:22:06 by mkuida           ###   ########.fr       */
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

static void	free_all_token_ptr(t_token **token_node_ptr)
{
	int	i;

	i = 0;
	while (token_node_ptr[i] != NULL)
	{
		if (token_node_ptr[i]->value != NULL)
			free(token_node_ptr[i]->value);
		if (token_node_ptr[i]->status != NULL)
			free(token_node_ptr[i]->status);
		free(token_node_ptr[i]);
		i++;
	}
	free(token_node_ptr);
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
		free_all_token_ptr(cmd_node->token);
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
