/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:10:32 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/11 18:26:27 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_token(t_token_type type)
{
	return (type == TYPE_REDIRECT_IN || type == TYPE_REDIRECT_OUT
		|| type == TYPE_REDIRECT_APPEND || type == TYPE_REDIRECT_HEREDOC);
}

void	handle_parse_error(t_token *tokens)
{
	fprintf(stderr, "Syntax error near unexpected token '%s'\n", tokens->value);
	exit(EXIT_FAILURE); // エラー発生時にプログラムを終了
}

int	get_redirect_type(t_token_type token_type)
{
	switch (token_type)
	{
	case TYPE_REDIRECT_IN:
		return (REDIRECT_IN);
	case TYPE_REDIRECT_OUT:
		return (REDIRECT_OUT);
	case TYPE_REDIRECT_APPEND:
		return (REDIRECT_APPEND);
	case TYPE_REDIRECT_HEREDOC:
		return (REDIRECT_HEREDOC);
	default:
		return (-1); // 無効なリダイレクト
	}
}

void	add_redirect_to_command(t_command *cmd, t_token *token)
{
	t_redirect	*redir;

	if (!token || !token->next)
	{
		fprintf(stderr, "Error: Missing file name for redirect\n");
		exit(EXIT_FAILURE);
	}
	redir = malloc(sizeof(t_redirect));
	if (!redir)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	redir->file_name = strdup(token->next->value);
	redir->type = get_redirect_type(token->status->token_type);
	redir->next = cmd->redirects;
	cmd->redirects = redir;
}

void	add_argument_to_command(t_command *cmd, char *arg)
{
	int		count;
	char	**new_args;

	count = 0;
	// 現在の引数の数をカウント
	if (cmd->args)
		while (cmd->args[count] != NULL)
			count++;
	// 新しい配列を割り当て
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// 古い配列を新しい配列にコピー
	for (int i = 0; i < count; i++)
		new_args[i] = cmd->args[i];
	// 新しい引数を追加
	new_args[count] = strdup(arg);
	if (!new_args[count])
	{
		perror("strdup");
		free(new_args);
		exit(EXIT_FAILURE);
	}
	// 終端を設定
	new_args[count + 1] = NULL;
	// 古い配列を解放
	free(cmd->args);
	// 新しい配列を設定
	cmd->args = new_args;
}

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->command_name = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_command	*parse_tokens_to_commands(t_token *tokens)
{
	t_command	*cmd_head;
	t_command	*current;

	cmd_head = NULL;
	current = NULL;
	while (tokens)
	{
		if (tokens->status->token_type == TYPE_WORD)
		{
			if (!current)
			{
				current = create_new_command();
				cmd_head = current;
			}
			if (!current->command_name)
				current->command_name = strdup(tokens->value);
			else
				add_argument_to_command(current, tokens->value);
		}
		else if (is_redirect_token(tokens->status->token_type))
		{
			add_redirect_to_command(current, tokens);
			tokens = tokens->next; // リダイレクト対象のファイル名
		}
		else if (tokens->status->token_type == TYPE_PIPE)
		{
			current->next = create_new_command();
			current = current->next;
		}
		else
		{
			handle_parse_error(tokens);
		}
		tokens = tokens->next;
	}
	// print_command_info(cmd_head); // 可視化用出力
	return (cmd_head);
}
