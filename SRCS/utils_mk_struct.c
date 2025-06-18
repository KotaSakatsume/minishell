/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mk_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:20:35 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/18 08:45:43 by mkuida           ###   ########.fr       */
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
