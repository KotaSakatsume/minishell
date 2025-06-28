/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:34:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/28 14:46:53 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_redirect_list(t_redirect **head, t_redirect **tail,
							  t_redirect *tr, t_cmd **cmd)
{
	if (*head == NULL)
	{
		*head = tr; // tail?
		*tail = tr;
		(*cmd)->redir = tr;
	}
	else
	{
		(*tail)->next = tr;
		*tail = tr;
	}
	return;
}

static bool check_type_redirect(t_token_type tt)
{
	if (tt == TYPE_REDIRECT_IN || tt == TYPE_REDIRECT_OUT || tt == TYPE_REDIRECT_APPEND || tt == TYPE_REDIRECT_HEREDOC)
		return (true);
	else
		return (false);
}

int advance_redirect(t_token **tok, t_redirect **head, t_redirect **tail,
					 t_cmd **cmd)
{
	t_token_type tt;
	t_redirect *tr;

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
			tr->filename = strdup((*tok)->value);
			advance_token(tok);
			set_redirect_list(head, tail, tr, cmd);
		}
		else
			break;
	}
	return (0);
}

static void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	size_t copy_size;
	size_t i;
	char *src;
	char *dst;

	if (new_size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		exit(1);
	src = (char *)ptr;
	dst = (char *)new_ptr;
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	i = 0;
	while (i < copy_size)
	{
		dst[i] = src[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

int advance_cmd(t_token **tok, t_cmd **cmd)
{
	while (*tok && (*tok)->status->token_type == TYPE_WORD)
	{
		(*cmd)->argv = ft_realloc((*cmd)->argv, sizeof(char *) * (((*cmd)->argc) + 1),
								  sizeof(char *) * (((*cmd)->argc) + 2));
		(*cmd)->token = ft_realloc((*cmd)->token, sizeof(t_token *) * (((*cmd)->argc) + 1),
								   sizeof(t_token *) * (((*cmd)->argc) + 2));
		(*cmd)->argv[(*cmd)->argc] = ft_strdup((*tok)->value);
		(*cmd)->token[(*cmd)->argc] = *tok;
		(*cmd)->argc++;
		(*cmd)->argv[(*cmd)->argc] = NULL;
		(*cmd)->token[(*cmd)->argc] = NULL;
		advance_token(tok);
	}
	return (0);
}
