/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token_to_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:53:21 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/18 07:53:42 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exchange_token_to_char(t_job *job_head)
{
	t_job *job_ptr;
	job_ptr = job_head;

	while (job_ptr != NULL)
	{
		token_to_char_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void token_to_char_pipeline(t_job *job_ptr)
{
	t_pipeline *pipeline_ptr;
	pipeline_ptr = job_ptr->pipeline;
	while (pipeline_ptr != NULL)
	{
		token_to_char_cmd(pipeline_ptr);
		pipeline_ptr = pipeline_ptr->next;
	}
}

void token_to_char_cmd(t_pipeline *pipeline_ptr)
{
	int i;
	i = 0;
	t_cmd *cmd_ptr;
	cmd_ptr = pipeline_ptr->cmd;
	if (cmd_ptr == NULL)
	{
		printf("error\n");
		exit(1);
	}
	t_token *token_ptr = cmd_ptr->token[i];
	char *char_ptr = cmd_ptr->argv[i];
	char *dest;
	int size = cmd_ptr->argc;

	while (char_ptr != NULL)
	{
		if(i >= size)
		{
			free(char_ptr);
			char_ptr = NULL;
		}
		else if (ft_strcmp(char_ptr, cmd_ptr->token[i]->value) != 0)
		{
			dest = ft_strdup(token_ptr->value);
			if (dest == NULL)
				exit(1);
			free(cmd_ptr->argv[i]);
			cmd_ptr->argv[i] = dest;
		}
		// free結合分
		i++;
		token_ptr = cmd_ptr->token[i];
		char_ptr = cmd_ptr->argv[i];
	}
}
