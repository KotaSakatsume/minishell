/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:34:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 15:34:41 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	advance_redirect(t_token **tok, t_redirect **head, t_redirect **tail,
		t_cmd **cmd)
{
	t_token_type	tt;
	t_redirect		*tr;

	while (*tok)
	{
		tt = (*tok)->status->token_type;
		if (tt == TYPE_REDIRECT_IN || tt == TYPE_REDIRECT_OUT
			|| tt == TYPE_REDIRECT_APPEND || tt == TYPE_REDIRECT_HEREDOC)
		{
			tr = mk_t_redirect();
			tr->type = tt;
			advance_token(tok);                       // redirectを消費
			if (check_token(tok, TYPE_WORD) == false) // 次はファイル名
			{
				printf("構文エラーがあります(redirect)\n");
				free(tr);
				return (1);
			}
			tr->filename = strdup((*tok)->value);
			advance_token(tok);
			if (*head == NULL)
			{
				*head = *tail = tr;
				(*cmd)->redir = tr;
			}
			else
			{
				(*tail)->next = tr;
				*tail = tr;
			}
		}
		else
			break ;
	}
	return (0);
}

int	advance_cmd(t_token **tok, t_cmd **cmd)
{
	while (*tok && (*tok)->status->token_type == TYPE_WORD)
	{
		(*cmd)->argv = realloc((*cmd)->argv, sizeof(char *) * (((*cmd)->argc)
					+ 2));
		(*cmd)->token = realloc((*cmd)->token, sizeof(t_token *)
				* (((*cmd)->argc) + 2));
		(*cmd)->argv[(*cmd)->argc] = ft_strdup((*tok)->value);
		(*cmd)->token[(*cmd)->argc] = *tok;
		(*cmd)->argc++;
		(*cmd)->argv[(*cmd)->argc] = NULL;
		(*cmd)->token[(*cmd)->argc] = NULL;
		advance_token(tok);
	}
	return (0);
}
