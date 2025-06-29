/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_end_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:55:53 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 17:36:30 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_mode(char *input)
{
	int	mode;

	if (ft_strncmp(input, "\'", 1) == 0)
		mode = MODE_SINGLE_QUOTE;
	else if (ft_strncmp(input, "\"", 1) == 0)
		mode = MODE_DOUBLE_QUOTE;
	else if (ft_strncmp(input, ";", 1) == 0)
		mode = MODE_SEMICOLON;
	else if (ft_strncmp(input, "|", 1) == 0)
		mode = MODE_PIPE;
	else if (ft_strncmp(input, ">>", 2) == 0)
		mode = MODE_REDIRECT_APPEND;
	else if (ft_strncmp(input, "<<", 2) == 0)
		mode = MODE_REDIRECT_HEREDOC;
	else if (ft_strncmp(input, ">", 1) == 0)
		mode = MODE_REDIRECT_OUT;
	else if (ft_strncmp(input, "<", 1) == 0)
		mode = MODE_REDIRECT_IN;
	else
		mode = MODE_NORMAL;
	return (mode);
}

char	*serach_end_ptr_quote(char *input, char end_word)
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

char	*serach_end_ptr_normal(char *input)
{
	while (*input != '\0' && !is_space(*input))
	{
		if (*input == '\\')
		{
			input++;
			if (*input == '\0')
				return (NULL);
		}
		if (*(input) == '\'' || *(input) == '"' || *(input) == ';'
			|| *(input) == '|' || *(input) == '>' || *(input) == '<')
			return (input);
		input++;
	}
	return (input);
}

char	*serach_end_ptr(char *input)
{
	int	mode;

	mode = set_mode(input);
	if (mode == MODE_SINGLE_QUOTE)
		return (serach_end_ptr_quote(input, '\''));
	else if (mode == MODE_DOUBLE_QUOTE)
		return (serach_end_ptr_quote(input, '"'));
	else if (mode == MODE_NORMAL)
		return (serach_end_ptr_normal(input));
	else if (mode == MODE_SEMICOLON || mode == MODE_PIPE
		|| mode == MODE_REDIRECT_IN || mode == MODE_REDIRECT_OUT)
	{
		input++;
		return (input);
	}
	else if (mode == MODE_REDIRECT_APPEND || mode == MODE_REDIRECT_HEREDOC)
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
