/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token_to_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:53:21 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 16:36:42 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exchange_token_to_char(t_job *job_head)
{
	t_job	*job_ptr;

	job_ptr = job_head;
	while (job_ptr != NULL)
	{
		token_to_char_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void	token_to_char_pipeline(t_job *job_ptr)
{
	t_pipeline	*pipeline_ptr;

	pipeline_ptr = job_ptr->pipeline;
	while (pipeline_ptr != NULL)
	{
		token_to_char_cmd(pipeline_ptr);
		pipeline_ptr = pipeline_ptr->next;
	}
}

static char	*modify_cmd_argv(t_cmd *cmd_ptr, int i)
{
	char	*dest;

	dest = ft_strdup(cmd_ptr->token[i]->value);
	if (dest == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	free(cmd_ptr->argv[i]);
	return (dest);
}

void	token_to_char_cmd(t_pipeline *pipeline_ptr)
{
	int		i;
	t_cmd	*cmd_ptr;

	i = 0;
	cmd_ptr = pipeline_ptr->cmd;
	if (cmd_ptr == NULL)
	{
		printf("error\n");
		exit(1);
	}
	if (cmd_ptr->token == NULL)
		return ;
	while (cmd_ptr->argv[i] != NULL)
	{
		if (i >= (cmd_ptr->argc))
		{
			free(cmd_ptr->argv[i]);
			cmd_ptr->argv[i] = NULL;
		}
		else if (ft_strcmp(cmd_ptr->argv[i], cmd_ptr->token[i]->value) != 0)
		{
			cmd_ptr->argv[i] = modify_cmd_argv(cmd_ptr, i);
		}
		i++;
	}
}
