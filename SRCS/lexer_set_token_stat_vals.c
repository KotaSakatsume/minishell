/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_token_stat_vals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 16:55:15 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_stat_vals(t_token_stat *token_stat_ptr, char *token_str)
{
	set_stat_token_type(token_stat_ptr, token_str);
	set_stat_token_in_quote(token_stat_ptr, token_str);
	set_stat_token_need_expand(token_stat_ptr);
}

void	set_stat_token_type(t_token_stat *token_stat_ptr, char *token_str)
{
	if (token_str == NULL)
	{
		perror("set_stat_token_type : token_str is NULL");
		exit(1);
	}
	if (strcmp(token_str, "|") == 0)
		token_stat_ptr->token_type = TYPE_PIPE;
	else if (strcmp(token_str, ">") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_OUT;
	else if (strcmp(token_str, "<") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_IN;
	else if (strcmp(token_str, ">>") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_APPEND;
	else if (strcmp(token_str, "<<") == 0)
		token_stat_ptr->token_type = TYPE_REDIRECT_HEREDOC;
	else if (strcmp(token_str, "'") == 0)
		token_stat_ptr->token_type = TYPE_QUOTE_SINGLE;
	else if (strcmp(token_str, "\"") == 0)
		token_stat_ptr->token_type = TYPE_QUOTE_DOUBLE;
	else if (strcmp(token_str, ";") == 0)
		token_stat_ptr->token_type = TYPE_SEMICOLON;
	else
		token_stat_ptr->token_type = TYPE_WORD;
}

void	set_stat_token_in_quote(t_token_stat *token_stat_ptr, char *token_str)
{
	if (token_str == NULL)
	{
		perror("set_stat_token_in_quote : token_str is NULL");
		exit(1);
	}
	if (ft_strlen(token_str) > 1)
	{
		if (token_str[0] == '\"' && token_str[ft_strlen(token_str) - 1] == '\"')
			token_stat_ptr->in_quote = QUOTE_DOUBLE;
		else if (token_str[0] == '\'' && token_str[ft_strlen(token_str)
				- 1] == '\'')
			token_stat_ptr->in_quote = QUOTE_SINGLE;
		else
			token_stat_ptr->in_quote = QUOTE_OUT;
	}
	else
		token_stat_ptr->in_quote = QUOTE_OUT;
}

void	set_stat_token_need_expand(t_token_stat *token_stat_ptr)
{
	if (token_stat_ptr->token_type == TYPE_WORD)
	{
		if (token_stat_ptr->in_quote == QUOTE_OUT
			|| token_stat_ptr->in_quote == QUOTE_DOUBLE)
			token_stat_ptr->need_expand = 1;
		else if (token_stat_ptr->in_quote == QUOTE_SINGLE)
			token_stat_ptr->need_expand = 0;
		else
		{
			perror("set_stat_token_need_expand : "
				"token_stat_ptr->in_quote is not valid");
			exit(1);
		}
	}
	else
		token_stat_ptr->need_expand = 0;
}
