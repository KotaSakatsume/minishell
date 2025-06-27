/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_daller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:33:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 12:35:03 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_end_daller_ptr(char *ptr)
{
	while (*ptr != '\0')
		ptr++;
	return (ptr);
}

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

char	*serch_indaller_str(char *daller_str_ptr, char *daller_end_ptr)
{
	char	*dest;
	int		i;

	i = 0;
	daller_str_ptr++;
	while ((daller_str_ptr) + i != (daller_end_ptr))
		i++;
	dest = ft_strndup(daller_str_ptr, i);
	return (dest);
}

char	*serch_and_expand_env(char *target, t_shell_env *t_shellenv_ptr)
{
	t_env	*env;
	char	*dest;

	env = t_shellenv_ptr->env_list;
	while ((env != NULL))
	{
		if (ft_strcmp(env->key, target) == 0)
		{
			dest = ft_strdup(env->value);
			return (dest);
		}
		env = env->next;
	}
	dest = malloc(sizeof(char) * 1);
	dest[0] = '\0';
	return (dest);
}

static void	check_and_expand_question_mode(char *daller_str_ptr,
		t_token *token_ptr, t_shell_env *t_shellenv_ptr)
{
	char	*daller_end_ptr;
	char	*temp_str;
	char	*ahead_str;
	char	*behind_str;

	daller_end_ptr = daller_str_ptr + 2;
	ahead_str = ft_strndup(token_ptr->value, ((daller_str_ptr)
				- (token_ptr->value)));
	behind_str = ft_strndup(daller_end_ptr, ft_strlen(daller_end_ptr));
	temp_str = combine_str_and_free_oldstr(ahead_str,
			ft_strdup(ft_itoa(t_shellenv_ptr->exit_status)));
	temp_str = combine_str_and_free_oldstr(temp_str, behind_str);
	free(token_ptr->value);
	token_ptr->value = temp_str;
}

static void	check_and_expand_normal_mode(char *daller_str_ptr,
		t_token *token_ptr, t_shell_env *t_shellenv_ptr)
{
	char	*daller_end_ptr;
	char	*indaller_str;
	char	*expandered_str;
	char	*temp_str;

	daller_end_ptr = search_end_daller_ptr(daller_str_ptr);
	indaller_str = ft_strndup((daller_str_ptr + 1), ft_strlen(daller_str_ptr
				+ 1));
	expandered_str = serch_and_expand_env(indaller_str, t_shellenv_ptr);
	temp_str = combine_str_and_free_oldstr(ft_strndup(token_ptr->value,
				((daller_str_ptr) - (token_ptr->value))), expandered_str);
	temp_str = combine_str_and_free_oldstr(temp_str, ft_strndup(daller_end_ptr,
				ft_strlen(daller_end_ptr)));
	free(token_ptr->value);
	token_ptr->value = temp_str;
}

static void	check_and_expand(t_token *token_ptr, t_shell_env *t_shellenv_ptr)
{
	char	*daller_str_ptr;

	while (serach_start_daller_ptr(token_ptr->value) != NULL)
	{
		daller_str_ptr = serach_start_daller_ptr(token_ptr->value);
		if (*(daller_str_ptr + 1) == '\0')
			return ;
		if (*(daller_str_ptr + 1) == '?')
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
