/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_daller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:53:28 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 16:36:23 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*serach_start_daller_ptr(char *input)
{
	while (*input != '\0')
	{
		if (*(input) == '$')
			return (input);
		if (*input == '\\')
		{
			input++;
			if (*input == '\0')
				return (NULL);
		}
		input++;
	}
	return (NULL);
}

static void	check_and_expand(t_token *token_ptr, t_shell_env *t_shellenv_ptr)
{
	char	*daller_str_ptr;

	while (serach_start_daller_ptr(token_ptr->value) != NULL)
	{
		daller_str_ptr = serach_start_daller_ptr(token_ptr->value);
		if (*(daller_str_ptr + 1) == '\0')
			return ;
		if (*(daller_str_ptr + 1) == '$')
		{
			check_and_expand_daller_mode(daller_str_ptr, token_ptr);
		}
		else if (*(daller_str_ptr + 1) == '?')
		{
			check_and_expand_question_mode(daller_str_ptr, token_ptr,
				t_shellenv_ptr);
		}
		else
		{
			check_and_expand_normal_mode(daller_str_ptr, token_ptr,
				t_shellenv_ptr);
		}
	}
}

void	extend_daller(t_pipeline *pipeline_ptr, t_shell_env *t_shellenv_ptr)
{
	int		i;
	t_cmd	*cmd_ptr;
	t_token	*token_ptr;

	i = 0;
	cmd_ptr = pipeline_ptr->cmd;
	if (cmd_ptr->token == NULL)
		return ;
	token_ptr = cmd_ptr->token[i];
	while (token_ptr != NULL)
	{
		if (token_ptr->status->in_quote == QUOTE_DOUBLE
			|| token_ptr->status->in_quote == QUOTE_OUT)
		{
			check_and_expand(token_ptr, t_shellenv_ptr);
		}
		i++;
		token_ptr = cmd_ptr->token[i];
	}
}
