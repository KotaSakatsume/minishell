/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_end_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:55:53 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/15 14:20:05 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (*input == '\0')
				return (NULL);
		}
		if (*(input) == '\'' || *(input) == '"' || *(input) == ';' || *(input) == '|' || *(input) == '>' || *(input) == '<')
			return (input);
		input++;
	}
	return (input);
}

char *serach_end_ptr(char *input)
{
	int mode;

	if (ft_strncmp(input, "\'", 1) == 0)
		mode = mode_single_quote;
	else if (ft_strncmp(input, "\"", 1) == 0)
		mode = mode_double_quote;
	else if (ft_strncmp(input, ";", 1) == 0)
		mode = mode_semicolon;
	else if (ft_strncmp(input, "|", 1) == 0)
		mode = mode_pipe;
	else if (ft_strncmp(input, ">>", 2) == 0)
		mode = mode_redirect_append;
	else if (ft_strncmp(input, "<<", 2) == 0)
		mode = mode_redirect_heredoc;
	else if (ft_strncmp(input, ">", 1) == 0)
		mode = mode_redirect_out;
	else if (ft_strncmp(input, "<", 1) == 0)
		mode = mode_redirect_in;
	else
		mode = mode_normal;

	char end_word;
	if (mode == mode_single_quote)
		return (serach_end_ptr_quote(input, '\''));
	else if (mode == mode_double_quote)
		return (serach_end_ptr_quote(input, '"'));
	else if (mode == mode_normal)
		return (serach_end_ptr_normal(input));
	else if (mode == mode_semicolon || mode == mode_pipe || mode == mode_redirect_in || mode == mode_redirect_out)
	{
		input++;
		return (input);
	}
	else if (mode == mode_redirect_append || mode == mode_redirect_heredoc)
	{
		input += 2;
		return (input);
	}
	else
	{
		perror("serach_end_ptr : mode is not valid");
		exit(1);
	}
}
