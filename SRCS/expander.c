/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/17 03:28:54 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void delete_quote(t_job *job_head);
static void delete_quote_pipeline(t_job *job_ptr);
static void delete_quote_cmd(t_pipeline *pipeline_ptr);
static void set_token_remove_quote(t_token *next_token_ptr);

static void set_token_remove_backslash(t_token *next_token_ptr, int count_backslash_to_remove);
static int check_token_remove_backslash(t_token *next_token_ptr);

static void exchange_token_to_char(t_job *job_head);
static void token_to_char_pipeline(t_job *job_ptr);
static void token_to_char_cmd(t_pipeline *pipeline_ptr);

static void combine_nospace_token(t_job *job_head);
static void combine_nospace_token_pipeline(t_job *job_ptr);
static void combine_main(t_pipeline *pipeline_ptr);
static int count_resized_token_len(t_token **token);
static void pad_dest(t_token **dest, int len, t_token **token);
static void free_olddest(t_token **token_head);
t_token *mk_empty_token();

void expander(t_job *job_head)
{
	// printf("expander: job_head = %p\n", (void *)job_head);
	// if (job_head == NULL)
	// {
	// 	printf("expander: job_head is NULL\n");
	// 	return;
	// }
	// printf("expander: job_head->pipeline = %p\n", (void *)job_head->pipeline);
	// if (job_head->pipeline == NULL)
	// {
	// 	printf("expander: job_head->pipeline is NULL\n");
	// 	return;
	// }
	// printf("expander: job_head->pipeline->cmd = %p\n", (void *)job_head->pipeline->cmd);
	// if (job_head->pipeline->cmd == NULL)
	// {
	// 	printf("expander: job_head->pipeline->cmd is NULL\n");
	// 	return;
	// }
	// printf("expander: job_head->pipeline->cmd->token = %p\n", (void *)job_head->pipeline->cmd->token);
	// if (job_head->pipeline->cmd->token == NULL)
	// {
	// 	printf("expander: job_head->pipeline->cmd->token is NULL\n");
	// 	return;
	// }

	delete_quote(job_head);
	combine_nospace_token(job_head);
	printf("test++\n");
	exchange_token_to_char(job_head);
	printf("test++sss\n");
	// printf("ok\n");
}

void delete_quote(t_job *job_head)
{
	t_job *job_ptr;
	job_ptr = job_head;

	while (job_ptr != NULL)
	{
		delete_quote_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void delete_quote_pipeline(t_job *job_ptr)
{
	t_pipeline *pipeline_ptr;
	pipeline_ptr = job_ptr->pipeline;
	while (pipeline_ptr != NULL)
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
	while (token_ptr != NULL)
	{
		token_ptr = cmd_ptr->token[i];
		if (token_ptr != NULL)
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

// combine

void combine_nospace_token(t_job *job_head)
{
	t_job *job_ptr;
	job_ptr = job_head;

	while (job_ptr != NULL)
	{
		combine_nospace_token_pipeline(job_ptr);
		job_ptr = job_ptr->next;
	}
}

void combine_nospace_token_pipeline(t_job *job_ptr)
{
	t_pipeline *pipeline_ptr;
	pipeline_ptr = job_ptr->pipeline;
	while (pipeline_ptr != NULL)
	{
		combine_main(pipeline_ptr);
		pipeline_ptr = pipeline_ptr->next;
	}
}

void combine_main(t_pipeline *pipeline_ptr)
{
	int len;
	int i;
	i = 0;
	t_cmd *cmd_ptr;
	t_token **dest;


	
	while (pipeline_ptr != NULL)
	{
		cmd_ptr = pipeline_ptr->cmd;

		len = count_resized_token_len(cmd_ptr->token);

		//
		printf("len = %d\n",len);
		printf("cmd_ptr->argc = %d\n",cmd_ptr->argc);
		cmd_ptr->argc = len;

		dest = malloc(sizeof(t_token *) * (len + 1));
		while(i < len)
		{
			dest[i] = mk_empty_token();
			i++;
		}
		dest[i] = NULL;

		pad_dest(dest, len, cmd_ptr->token);
		free_olddest(cmd_ptr->token);
		cmd_ptr->token = dest;
		pipeline_ptr = pipeline_ptr->next;
	}
}

int count_resized_token_len(t_token **token)
{
	int ans;
	ans = 0;
	int i;
	i = 0;
	int before_after_space_is;
	int before_token_id;
	int marge_id;
	marge_id = 0;

	while (token[i] != NULL)
	{
		if (i == 0)
			ans++;
		else if (!(before_after_space_is == 0 && (before_token_id + 1 == token[i]->id)))
		{
			ans++;
			marge_id++;
		}
		token[i]->marge_id = marge_id;
		before_after_space_is = token[i]->status->after_space_is;
		before_token_id = token[i]->id;
		i++;
	}
	return (ans);
}

void pad_dest(t_token **dest, int len, t_token **token)
{
	int i;
	int marge_id;
	char *temp;
	t_token *token_ptr;

	printf("test1\n");
	fflush(stdout);

	i = 0;
	token_ptr = token[i];
	while (token_ptr != NULL)
	{
		if (dest[token_ptr->marge_id]->value == NULL)
			dest[token_ptr->marge_id]->value = ft_strdup(token_ptr->value);
		else
		{
			temp = ft_strjoin(dest[token_ptr->marge_id]->value, (token_ptr->value));
			free(dest[token_ptr->marge_id]->value);
			dest[token_ptr->marge_id]->value = temp;
		}
		i++;
		token_ptr = token[i];
	}
	return;
}

void free_olddest(t_token **token_head)
{
	int i;
	i = 0;
	while (token_head[i] != NULL)
	{
		free(token_head[i]->status);
		free(token_head[i]);
		i++;
	}
	free(token_head[i]);
	free(token_head);
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