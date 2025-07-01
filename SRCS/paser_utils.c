/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:58 by mkuida            #+#    #+#             */
/*   Updated: 2025/07/01 10:25:19 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	advance_token(t_token **token)
{
	if (token == NULL)
	{
		write(2, "parse error:advance_token\n", 26);
		exit(1);
	}
	*token = (*token)->next;
}

bool	accept_token(t_token **token, t_token_type type)
{
	if (token != NULL && *token != NULL && (*token)->status->token_type == type)
	{
		advance_token(token);
		return (true);
	}
	return (false);
}

bool	check_token(t_token **token, t_token_type type)
{
	if (token != NULL && *token != NULL && (*token)->status->token_type == type)
	{
		return (true);
	}
	return (false);
}

void	expect_token(t_token **tok, t_token_type type)
{
	static char	*token_type_names[11];

	token_type_names[TYPE_INITIAL] = "INITIAL";
	token_type_names[TYPE_WORD] = "WORD";
	token_type_names[TYPE_PIPE] = "PIPE";
	token_type_names[TYPE_REDIRECT_IN] = "REDIRECT_IN";
	token_type_names[TYPE_REDIRECT_OUT] = "REDIRECT_OUT";
	token_type_names[TYPE_REDIRECT_APPEND] = "REDIRECT_APPEND";
	token_type_names[TYPE_REDIRECT_HEREDOC] = "REDIRECT_HEREDOC";
	token_type_names[TYPE_QUOTE_SINGLE] = "QUOTE_SINGLE";
	token_type_names[TYPE_QUOTE_DOUBLE] = "QUOTE_DOUBLE";
	token_type_names[TYPE_SEMICOLON] = "SEMICOLON";
	token_type_names[TYPE_EOF] = "EOF";
	if (!accept_token(tok, type))
	{
		write(2, "parse error: expected ", 22);
		write(2, token_type_names[type], ft_strlen(token_type_names[type]));
		write(2, "\n", 1);
		exit(1);
	}
}
