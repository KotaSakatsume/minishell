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
    int i = 0;
    t_cmd *cmd_ptr = pipeline_ptr->cmd;

    if (cmd_ptr == NULL)
    {
        printf("error\n");
        exit(1);
    }

    while (i < cmd_ptr->argc && cmd_ptr->argv[i] != NULL)
    {
        t_token *token_ptr = cmd_ptr->token[i];
        if (token_ptr == NULL)
            break;

        if (ft_strcmp(cmd_ptr->argv[i], token_ptr->value) != 0)
        {
            free(cmd_ptr->argv[i]);
            cmd_ptr->argv[i] = ft_strdup(token_ptr->value);
            if (cmd_ptr->argv[i] == NULL)
                exit(1);
        }
        i++;
    }

    // argcより後ろはすべてNULLに揃える（argvはNULL終端）
    while (cmd_ptr->argv[i] != NULL)
    {
        free(cmd_ptr->argv[i]);
        cmd_ptr->argv[i] = NULL;
        i++;
    }
}
