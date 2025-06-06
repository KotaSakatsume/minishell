/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/06 21:27:32 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	delete_quote(t_job *job_head);
static void delete_quote_pipeline(t_job *job_ptr);
static void delete_quote_cmd(t_pipeline *pipeline_ptr);
static void set_token_remove_quote(t_token *next_token_ptr);

static void set_token_remove_backslash(t_token *next_token_ptr, int count_backslash_to_remove);
static int check_token_remove_backslash(t_token *next_token_ptr);

static void exchange_token_to_char(t_job *job_head);
static void token_to_char_pipeline(t_job *job_ptr)	;
static void token_to_char_cmd(t_pipeline *pipeline_ptr);


void	expander(t_job *job_head)
{
	// expand_doller(job_head);
	delete_quote(job_head);
	// combine_nospace_token(job_head);
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

void delete_quote_pipeline(t_job *job_ptr)	
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
	int i;
	i = 0;
	t_cmd *cmd_ptr;
	cmd_ptr = pipeline_ptr->cmd;
	t_token *token_ptr = cmd_ptr->token[i];
	int count_backslash_to_remove_check;
	while(token_ptr != NULL)
	{
		token_ptr = cmd_ptr->token[i];
		if(token_ptr != NULL)
		{
			// printf("i=%d\n",i);
			if (token_ptr->status->in_quote == QUOTE_SINGLE || token_ptr->status->in_quote == QUOTE_DOUBLE)
				set_token_remove_quote(token_ptr);
			count_backslash_to_remove_check = check_token_remove_backslash(token_ptr);
			if (count_backslash_to_remove_check != 0)
				set_token_remove_backslash(token_ptr, count_backslash_to_remove_check);
			i++;
		}
	}
}


void set_token_remove_quote(t_token *next_token_ptr)
{
	char *dest;
	int len;
	int i;

	i = 0;
	len = ft_strlen(next_token_ptr->value);
	dest = malloc(len + 1 - 2);
	if (dest == NULL)
	{
		perror("set_token_remove_quote : dest is NULL");
		exit(1);
	}
	while (i < len - 2)
	{
		dest[i] = next_token_ptr->value[i + 1];
		i++;
	}
	dest[i] = '\0';
	free(next_token_ptr->value);
	next_token_ptr->value = dest;
}

int check_token_remove_backslash(t_token *next_token_ptr)
{
	int count_backslash_to_remove;
	int i;

	i = 0;
	count_backslash_to_remove = 0;

	while (next_token_ptr->value[i] != '\0')
	{
		if (next_token_ptr->value[i] == '\\')
		{
			count_backslash_to_remove++;
			i++;
		}
		i++;
	}
	// printf("count_backslash_to_remove : %d\n", count_backslash_to_remove);
	return (count_backslash_to_remove);
}

void set_token_remove_backslash(t_token *next_token_ptr, int count_backslash_to_remove)
{
	int i;
	int j;
	char *dest;

	dest = malloc(ft_strlen(next_token_ptr->value) - count_backslash_to_remove + 1);
	if (dest == NULL)
	{
		perror("set_token_remove_backslash : dest is NULL");
		exit(1);
	}

	i = 0;
	j = 0;
	while (next_token_ptr->value[i + j] != '\0')
	{
		if (next_token_ptr->value[i + j] == '\\')
		{
			j++;
		}
		dest[i] = next_token_ptr->value[i + j];
		i++;
	}
	dest[i] = '\0';
	free(next_token_ptr->value);
	next_token_ptr->value = dest;
}

void exchange_token_to_char(t_job *job_head)
{
	t_job *job_ptr;
	job_ptr = job_head;

	while(job_ptr != NULL)
	{
		token_to_char_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void token_to_char_pipeline(t_job *job_ptr)	
{
	t_pipeline *pipeline_ptr;
	pipeline_ptr = job_ptr->pipeline;
	while(pipeline_ptr != NULL)
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
	t_token *token_ptr = cmd_ptr->token[i];
	char *char_ptr = cmd_ptr->argv[i];
	char *dest;
	
		while(char_ptr != NULL)
		{
			if(cmd_ptr == NULL)
			{
				printf("error\n");
				exit(1);
			}
			
			if(ft_strcmp(char_ptr,cmd_ptr->token[i]->value) != 0)
			{
				dest = ft_strdup(token_ptr->value);
				if(dest == NULL)
					exit(1);
				free(cmd_ptr->argv[i]);
				cmd_ptr->argv[i] = dest;
			}
			//free結合分
			i++;
			token_ptr = cmd_ptr->token[i];
			char_ptr = cmd_ptr->argv[i];
		}
}
