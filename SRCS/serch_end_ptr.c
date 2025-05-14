/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_end_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:55:53 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/14 14:27:26 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *serach_end_ptr_quote(char *input, char end_word)
{
	input++;
	while (*input != end_word && *input != '\0')
	{
		if (*input == '\\')
		{
			input++;
			if (*input == '\0')
				return (NULL);
		}
		input++;
	}
	if (*input == '\0')
		return (NULL);
	else if (*input != '\0')
	{
		input++;
		return (input);
	}
	else
	{
		perror("serach_end_ptr_quote : input is not valid");
		exit(1);
	}
}

char *serach_end_ptr_normal(char *input)
{
	while (*input != '\0' && !is_space(*input))
	{
		if (*input == '\\')
		{
			input++;
			if(*input == '\0')
				return (NULL);
		}
		input++;
	}
	return (input);
}



char *serach_end_ptr(char *input, int mode)
{
	char end_word;
	if (mode == mode_single_quote)
		return(serach_end_ptr_quote(input,'\''));
	else if (mode == mode_double_quote)
		return(serach_end_ptr_quote(input,'"'));
	else if (mode == mode_normal)
		return(serach_end_ptr_normal(input));
	else
	{
		perror("serach_end_ptr : mode is not valid");
		exit(1);
	}
}

