/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:41:55 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/27 10:26:57 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_readline_continue(char *input)
{
	char	*end_ptr;

	while (*input != '\0')
	{
		end_ptr = serach_end_ptr(input);
		if (end_ptr == NULL) // read_continue
			return (1);
		input = end_ptr;
		while (is_space(*input))
			input++;
	}
	return (0);
}

static void	free_all_shellenv(t_shell_env *t_shellenv_ptr)
{
	int	i;

	i = 0;
	free_env_list(t_shellenv_ptr->env_list);
	while (t_shellenv_ptr->envp[i] != NULL)
	{
		free(t_shellenv_ptr->envp[i]);
		i++;
	}
	free(t_shellenv_ptr->envp[i]);
	free(t_shellenv_ptr->envp);
	free(t_shellenv_ptr);
}

char	*readline_seq(t_shell_env	*t_shellenv_ptr)
{
	char	*input;
	char	*temp;

	input = readline("minishell > ");
	if (!input)
	{
		free_all_shellenv(t_shellenv_ptr);
		printf("exit\n");
		exit(0);
	}
	if (*input != '\0')
	{
		while (check_readline_continue(input) == 1)
		{
			temp = readline(" > ");
			if (!temp)
			{
				printf("予期しないファイル終了 (EOF) です\nexit\n");
				exit(-1);
			}
			input = combine_str_and_free_oldstr(input, temp);
		}
	}
	return (input);
}
