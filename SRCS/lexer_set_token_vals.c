/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_token_vals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/19 17:59:33 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_token_remove_backslash(t_token *next_token_ptr, int count_backslash_to_remove)
{
	int i;
	int j;
	char *dest;

	dest = malloc(ft_strlen(next_token_ptr->value) - count_backslash_to_remove + 1);
	if (dest == NULL)
	{
		perror("set_token_remove_backslash : dest is NULL");
		exit(1);
	}

	i = 0;
	j = 0;
	while (next_token_ptr->value[i + j] != '\0')
	{
		if (next_token_ptr->value[i + j] == '\\')
		{
			j++;
		}
		dest[i] = next_token_ptr->value[i + j];
		i++;
	}
	dest[i] = '\0';
	free(next_token_ptr->value);
	next_token_ptr->value = dest;
}

int check_token_remove_backslash(t_token *next_token_ptr)
{
	int count_backslash_to_remove;
	int i;

	i = 0;
	count_backslash_to_remove = 0;

	while (next_token_ptr->value[i] != '\0')
	{
		if (next_token_ptr->value[i] == '\\')
		{
			count_backslash_to_remove++;
			i++;
		}
		i++;
	}
	// printf("count_backslash_to_remove : %d\n", count_backslash_to_remove);
	return (count_backslash_to_remove);
}

void set_token_remove_quote(t_token *next_token_ptr)
{
	char *dest;
	int len;
	int i;

	i = 0;
	len = ft_strlen(next_token_ptr->value);
	dest = malloc(len + 1 - 2);
	if (dest == NULL)
	{
		perror("set_token_remove_quote : dest is NULL");
		exit(1);
	}
	while (i < len - 2)
	{
		dest[i] = next_token_ptr->value[i + 1];
		i++;
	}
	dest[i] = '\0';
	free(next_token_ptr->value);
	next_token_ptr->value = dest;
}

void set_stat_token_need_expand(t_token_stat *token_stat_ptr)
{
	if (token_stat_ptr->token_type == TYPE_WORD)
	{
		if (token_stat_ptr->in_quote == QUOTE_OUT || token_stat_ptr->in_quote == QUOTE_DOUBLE)
			token_stat_ptr->need_expand = 1;
		else if (token_stat_ptr->in_quote == QUOTE_SINGLE)
			token_stat_ptr->need_expand = 0;
		else
		{
			perror("set_stat_token_need_expand : token_stat_ptr->in_quote is not valid");
			exit(1);
		}
	}
	else
		token_stat_ptr->need_expand = 0;
}

void set_stat_token_type(t_token_stat *token_stat_ptr, char *token_str)
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

void set_id(t_token **head)
{
	int i;
	t_token *node_ptr;

	i = 0;
	if (head == NULL || *head == NULL)
		return;
	node_ptr = *head;
	while (node_ptr != NULL)
	{
		node_ptr->id = i;
		node_ptr = node_ptr->next;
		i++;
	}
}

void set_stat_token_in_quote(t_token_stat *token_stat_ptr, char *token_str)
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
		else if (token_str[0] == '\'' && token_str[ft_strlen(token_str) - 1] == '\'')
			token_stat_ptr->in_quote = QUOTE_SINGLE;
		else
			token_stat_ptr->in_quote = QUOTE_OUT;
	}
	else
		token_stat_ptr->in_quote = QUOTE_OUT;
}

void set_token_stat_vals(t_token_stat *token_stat_ptr, char *token_str)
{
	set_stat_token_type(token_stat_ptr, token_str);
	set_stat_token_in_quote(token_stat_ptr, token_str);
	set_stat_token_need_expand(token_stat_ptr);
}

int set_token_marge_id(t_token *current_token_ptr, int marge_id)
{
	current_token_ptr->marge_id = marge_id;
	marge_id++;
	if (current_token_ptr->status->token_type == TYPE_WORD && current_token_ptr->status->after_space_is == 0)
	{
		if (current_token_ptr->next != NULL && current_token_ptr->next->status->token_type == TYPE_WORD)
			marge_id--;
	}
	return (marge_id);
}

void lexer_set_token_vals(t_token **head)
{
	char *token_str;
	int count_backslash_to_remove;
	t_token *next_token_ptr;
	next_token_ptr = *head;
	int marge_id = 0;

	set_id(head);

	while (next_token_ptr != NULL)
	{
		token_str = next_token_ptr->value;
		set_token_stat_vals(next_token_ptr->status, token_str);
		if (next_token_ptr->status->in_quote == QUOTE_SINGLE || next_token_ptr->status->in_quote == QUOTE_DOUBLE)
			set_token_remove_quote(next_token_ptr);
		count_backslash_to_remove = check_token_remove_backslash(next_token_ptr);
		if (count_backslash_to_remove != 0)
			set_token_remove_backslash(next_token_ptr, count_backslash_to_remove);
		next_token_ptr = next_token_ptr->next;
	}
	
	next_token_ptr = *head;
	while(next_token_ptr != NULL)
	{
		marge_id = set_token_marge_id(next_token_ptr, marge_id);
		next_token_ptr = next_token_ptr->next;
	}
}
