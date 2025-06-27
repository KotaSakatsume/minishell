/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_nospace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:53:28 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 09:19:57 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	combine_main(t_pipeline *pipeline_ptr)
{
	int		len;
	int		i;
	t_cmd	*cmd_ptr;
	t_token	**dest;

	cmd_ptr = pipeline_ptr->cmd;
	len = count_resized_token_len(cmd_ptr->token);
	cmd_ptr->argc = len;
	dest = malloc(sizeof(t_token *) * (len + 1));
	i = 0;
	while (i < len)
	{
		dest[i] = mk_empty_token();
		i++;
	}
	dest[i] = NULL;
	pad_dest(dest, len, cmd_ptr->token);
	free_olddest(cmd_ptr->token);
	cmd_ptr->token = dest;
}

int	count_resized_token_len(t_token **token)
{
	int	ans;
	int	i;
	int	before_after_space_is;
	int	before_token_id;
	int	marge_id;

	ans = 0;
	i = 0;
	marge_id = 0;
	while (token[i] != NULL)
	{
		if (i == 0)
			ans++;
		else if (!(before_after_space_is == 0 && (before_token_id
					+ 1 == token[i]->id)))
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

void	pad_dest(t_token **dest, int len, t_token **token)
{
	int		i;
	char	*temp;
	t_token	*token_ptr;

	i = 0;
	(void)len;
	token_ptr = token[i];
	while (token_ptr != NULL)
	{
		if (dest[token_ptr->marge_id]->value == NULL)
			dest[token_ptr->marge_id]->value = ft_strdup(token_ptr->value);
		else
		{
			temp = ft_strjoin(dest[token_ptr->marge_id]->value,
					(token_ptr->value));
			free(dest[token_ptr->marge_id]->value);
			dest[token_ptr->marge_id]->value = temp;
		}
		i++;
		token_ptr = token[i];
	}
	return ;
}

void	free_olddest(t_token **token_head)
{
	int	i;

	i = 0;
	while (token_head[i] != NULL)
	{
		if (token_head[i]->value != NULL)
			free(token_head[i]->value);
		free(token_head[i]->status);
		free(token_head[i]);
		i++;
	}
	free(token_head[i]);
	free(token_head);
}
