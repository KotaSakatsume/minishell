/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_daller_check_and_expand_mode.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:53:28 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 17:19:56 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*serch_and_expand_env(char *target, t_shell_env *t_shellenv_ptr)
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

static char	*search_end_daller_ptr(char *ptr)
{
	while (*ptr != '\0' && *ptr != '$')
		ptr++;
	return (ptr);
}

void	check_and_expand_question_mode(char *daller_str_ptr,
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
			ft_itoa(t_shellenv_ptr->exit_status_now));
	temp_str = combine_str_and_free_oldstr(temp_str, behind_str);
	free(token_ptr->value);
	token_ptr->value = temp_str;
}

void	check_and_expand_normal_mode(char *daller_str_ptr,
		t_token *token_ptr, t_shell_env *t_shellenv_ptr)
{
	char	*daller_end_ptr;
	char	*indaller_str;
	char	*expandered_str;
	char	*temp_str;

	daller_end_ptr = search_end_daller_ptr(daller_str_ptr + 1);
	indaller_str = ft_strndup((daller_str_ptr + 1), (daller_end_ptr
				- (daller_str_ptr + 1)));
	// printf("str = %p : end = %p\n",daller_str_ptr,daller_end_ptr);
	// printf("indaller_str = %s\n",indaller_str);
	expandered_str = serch_and_expand_env(indaller_str, t_shellenv_ptr);
	free(indaller_str);
	temp_str = combine_str_and_free_oldstr(ft_strndup(token_ptr->value,
				((daller_str_ptr) - (token_ptr->value))), expandered_str);
	temp_str = combine_str_and_free_oldstr(temp_str, ft_strndup(daller_end_ptr,
				ft_strlen(daller_end_ptr)));
	free(token_ptr->value);
	token_ptr->value = temp_str;
}

void	check_and_expand_daller_mode(char *daller_str_ptr,
		t_token *token_ptr)
{
	char	*daller_end_ptr;
	char	*temp_str;
	char	*ahead_str;
	char	*behind_str;

	daller_end_ptr = daller_str_ptr + 2;
	ahead_str = ft_strndup(token_ptr->value, ((daller_str_ptr)
				- (token_ptr->value)));
	behind_str = ft_strndup(daller_end_ptr, ft_strlen(daller_end_ptr));
	temp_str = combine_str_and_free_oldstr(ahead_str, behind_str);
	free(token_ptr->value);
	token_ptr->value = temp_str;
}
