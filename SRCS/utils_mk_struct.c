/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mk_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:20:35 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/19 17:56:28 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_cmd *mk_t_cmd()
{
	t_cmd* dest;
	dest = malloc(1*sizeof(t_cmd));
	if(dest == NULL)
		exit(1);
	dest->argv = NULL;
	dest->argc = 0;
	dest->redir = NULL;
	dest->token = NULL;
	return (dest);
}

t_job *mk_t_job()
{
	t_job* dest;
	dest = malloc(1*sizeof(t_job));
	if(dest == NULL)
		exit(1);
	dest->pipeline = NULL;
	dest->sep = SEP_NONE;
	dest->next = NULL;
	return (dest);
}

t_pipeline *mk_t_pipeline()
{
	t_pipeline *dest;
	dest = malloc(1*sizeof(t_pipeline));
	if(dest == NULL)
		exit(1);
	dest->cmd  = NULL;
	dest->next = NULL;
	return (dest);
}

t_redirect *mk_t_redirect()
{
	t_redirect *dest;
	dest = malloc(1*sizeof(t_redirect));
	if(dest == NULL)
		exit(1);
	dest->type=TYPE_INITIAL;
	dest->filename=NULL;
	dest->next=NULL;
	return (dest);
}

t_token *mk_t_token(char *start_ptr, char *end_ptr)
{
	t_token *t_token_node;
	t_token_node = malloc(sizeof(t_token));
	if (t_token_node == NULL)
	{
		perror("mk_t_token : malloc");
		return (NULL);
	}
	initialize_t_token(t_token_node);
	t_token_node->value = ft_strndup(start_ptr, end_ptr - start_ptr);
	if (t_token_node->value == NULL)
	{
		free(t_token_node);
		return (NULL);
	}
	t_token_node->status = malloc(sizeof(t_token_stat));
	if (t_token_node->status == NULL)
	{
		perror("mk_t_token : malloc");
		free(t_token_node->value);
		free(t_token_node);
		return (NULL);
	}
	initialize_t_token_stat(t_token_node->status);
	return (t_token_node);
}
