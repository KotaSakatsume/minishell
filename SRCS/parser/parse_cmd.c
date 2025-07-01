/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:34:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/29 18:32:08 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_cmd(t_token **tok, t_shell_env *t_shellenv_ptr)
{
	t_cmd		*cmd;
	t_redirect	*head;
	t_redirect	*tail;

	cmd = mk_t_cmd();
	head = NULL;
	tail = NULL;
	if (advance_redirect(tok, &head, &tail, &cmd) != 0)
	{
		t_shellenv_ptr->exit_status = 2;
		return (cmd);
	}
	advance_cmd(tok, &cmd);
	if (advance_redirect(tok, &head, &tail, &cmd) != 0)
	{
		t_shellenv_ptr->exit_status = 2;
		return (cmd);
	}
	if (cmd->argc == 0 && cmd->redir == NULL)
	{
		printf("構文エラーがあります (no cmd)\n");
		t_shellenv_ptr->exit_status = 2;
		return (cmd);
	}
	return (cmd);
}

static void	set_redirect_list(t_redirect **head, t_redirect **tail,
		t_redirect *tr, t_cmd **cmd)
{
	if (*head == NULL)
	{
		*head = tr;
		*tail = tr;
		(*cmd)->redir = tr;
	}
	else
	{
		(*tail)->next = tr;
		*tail = tr;
	}
	return ;
}

static bool	check_type_redirect(t_token_type tt)
{
	if (tt == TYPE_REDIRECT_IN || tt == TYPE_REDIRECT_OUT
		|| tt == TYPE_REDIRECT_APPEND || tt == TYPE_REDIRECT_HEREDOC)
		return (true);
	else
		return (false);
}

int	advance_redirect(t_token **tok, t_redirect **head, t_redirect **tail,
		t_cmd **cmd)
{
	t_token_type	tt;
	t_redirect		*tr;

	while (*tok)
	{
		tt = (*tok)->status->token_type;
		if (check_type_redirect(tt) == true)
		{
			tr = mk_t_redirect();
			tr->type = tt;
			advance_token(tok);
			if (check_token(tok, TYPE_WORD) == false)
			{
				printf("構文エラーがあります (redirect)\n");
				free(tr);
				return (1);
			}
			tr->filename = ft_strdup((*tok)->value);
			advance_token(tok);
			set_redirect_list(head, tail, tr, cmd);
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
		(*cmd)->argv = ft_realloc((*cmd)->argv, sizeof(char *) * (((*cmd)->argc)
					+ 1), sizeof(char *) * (((*cmd)->argc) + 2));
		(*cmd)->token = ft_realloc((*cmd)->token, sizeof(t_token *)
				* (((*cmd)->argc) + 1), sizeof(t_token *) * (((*cmd)->argc)
					+ 2));
		(*cmd)->argv[(*cmd)->argc] = ft_strdup((*tok)->value);
		(*cmd)->token[(*cmd)->argc] = *tok;
		(*cmd)->argc++;
		(*cmd)->argv[(*cmd)->argc] = NULL;
		(*cmd)->token[(*cmd)->argc] = NULL;
		advance_token(tok);
	}
	return (0);
}
