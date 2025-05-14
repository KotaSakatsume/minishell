/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_end_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:55:53 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/14 13:56:51 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *serach_end_ptr(char *input, int mode)
{
	char end_word;
	if (mode == mode_single_quote)
		end_word = '\'';
	else if (mode == mode_double_quote)
		end_word = '"';
	else if (mode == mode_normal)
	{
		while (*input != '\0' && !is_space(*input))
			input++;
		return (input);
	}
	else
	{
		perror("serach_end_ptr : mode is not valid");
		exit(1);
	}

	input++;
	while (*input != end_word && *input != '\0')
	{
		if (*input == '\\')
		{
			input++;
			if (*input == '\0')
				return (input);
		}
		input++;
	}
	if (*input != '\0')
		input++;
	return (input);
}
