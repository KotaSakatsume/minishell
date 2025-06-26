/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:41:55 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 17:26:23 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_readline_continue(char *input)
{
	char	*start_ptr;
	char	*end_ptr;
	int		after_space_exist;

	while (*input != '\0')
	{
		start_ptr = input;
		after_space_exist = 0;
		end_ptr = serach_end_ptr(input);
		if (end_ptr == NULL) // read_continue
			return (1);
		input = end_ptr;
		while (is_space(*input))
		{
			after_space_exist = 1;
			input++;
		}
	}
	return (0);
}

char	*readline_seq(void)
{
	char	*input;
	char	*temp;

	// char *concat;
	input = readline("minishell > ");
	if (!input)
	{
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
