/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:41:55 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/20 05:27:47 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_readline_continue(char *input)
{
	char *start_ptr;
	char *end_ptr;
	int after_space_exist;

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

char *readline_seq()
{
	char *input;
	char *temp;
	char *concat;

	input = readline("minishell > ");
	if(!input)
	{
		printf ("exit\n");
		exit (0);
	}
	if(*input != '\0')
	{
		while(check_readline_continue(input) == 1)
		{
			temp = readline(" > ");
			if(!temp)
			{
				printf ("予期しないファイル終了 (EOF) です\n");
				exit (-1);
			}
			concat = ft_strjoin(input,temp);
			free(input);
			free(temp);
			input = concat;
		}
	}
	return (input);
}

