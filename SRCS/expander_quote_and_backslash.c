/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote_and_backslash.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:50:06 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/18 07:52:40 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_quote_cmd(t_pipeline *pipeline_ptr)
{
	int		i;
	t_cmd	*cmd_ptr;
	t_token	*token_ptr;
	int		count_backslash_to_remove_check;

	i = 0;
	cmd_ptr = pipeline_ptr->cmd;
	token_ptr = cmd_ptr->token[i];
	while (token_ptr != NULL)
	{
		token_ptr = cmd_ptr->token[i];
		if (token_ptr != NULL)
		{
			if (token_ptr->status->in_quote == QUOTE_SINGLE
				|| token_ptr->status->in_quote == QUOTE_DOUBLE)
				set_token_remove_quote(token_ptr);
			count_backslash_to_remove_check = check_token_remove_backslash(token_ptr);
			if (count_backslash_to_remove_check != 0)
				set_token_remove_backslash(token_ptr,
					count_backslash_to_remove_check);
			i++;
		}
	}
}

void	set_token_remove_quote(t_token *next_token_ptr)
{
	char	*dest;
	int		len;
	int		i;

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

int	check_token_remove_backslash(t_token *next_token_ptr)
{
	int	count_backslash_to_remove;
	int	i;

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
	return (count_backslash_to_remove);
}

void	set_token_remove_backslash(t_token *next_token_ptr,
		int count_backslash_to_remove)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc(ft_strlen(next_token_ptr->value) - count_backslash_to_remove
			+ 1);
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
