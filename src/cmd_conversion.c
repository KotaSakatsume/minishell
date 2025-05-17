/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:10:32 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/16 18:48:05 by kosakats         ###   ########.fr       */
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

	if (!token->next)
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
	cmd->cmd_name = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

// t_command	*parse_tokens_to_commands(t_token *tokens)
// {
// 	t_command	*cmd_head;
// 	t_command	*current;

// 	cmd_head = NULL;
// 	current = NULL;
// 	while (tokens)
// 	{
// 		if (tokens->status->token_type == TYPE_WORD)
// 		{
// 			if (!current)
// 			{
// 				current = create_new_command();
// 				cmd_head = current;
// 			}
// 			if (!current->command_name)
// 				current->command_name = strdup(tokens->value);
// 			else
// 				add_argument_to_command(current, tokens->value);
// 		}
// 		else if (is_redirect_token(tokens->status->token_type))
// 		{
// 			add_redirect_to_command(current, tokens);
// 			tokens = tokens->next; // リダイレクト対象のファイル名
// 		}
// 		else if (tokens->status->token_type == TYPE_PIPE)
// 		{
// 			current->next = create_new_command();
// 			current = current->next;
// 		}
// 		else
// 		{
// 			handle_parse_error(tokens);
// 		}
// 		tokens = tokens->next;
// 	}
// 	// print_command_info(cmd_head); // 可視化用出力
// 	return (cmd_head);
// }

void	add_command_to_list(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*temp;

	if (!new_cmd)
		return ; // new_cmd が NULL の場合は何もしない
	if (!*cmd_list)
	{
		// cmd_list が空の場合、新しいコマンドをリストの先頭に設定
		*cmd_list = new_cmd;
	}
	else
	{
		// 既存の cmd_list の最後に新しいコマンドを追加
		temp = *cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
	new_cmd->next = NULL; // new_cmd の next を明示的に NULL に設定
}

t_redirect	*create_redirect(t_token *token)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
	{
		perror("Failed to allocate memory for redirect");
		exit(1);
	}
	redir->type = token->status->token_type;
	redir->file_name = NULL;
	redir->next = NULL;
	return (redir);
}

t_command	*create_and_add_command(t_command **cmd_list)
{
	t_command	*cmd;

	cmd = create_new_command();
	add_command_to_list(cmd_list, cmd);
	return (cmd);
}

t_command	*parse_tokens_to_commands(t_token *tokens)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_redirect	*redir;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (tokens->status->token_type == TYPE_WORD)
		{
			if (!current_cmd)
				current_cmd = create_and_add_command(&cmd_list);
			if (!current_cmd->cmd_name)
				current_cmd->cmd_name = strdup(tokens->value);
			else
				add_argument_to_command(current_cmd, tokens->value);
		}
		else if (is_redirect_token(tokens->status->token_type))
		{
			if (!current_cmd)
				current_cmd = create_and_add_command(&cmd_list);
			redir = create_redirect(tokens);
			tokens = tokens->next; // Move to the redirect target
			if (!tokens || tokens->status->token_type != TYPE_WORD)
			{
				fprintf(stderr,
					"Syntax error: Missing redirect target after redirect token\n");
				exit(1);
			}
			redir->file_name = strdup(tokens->value);
			printf("redir->file_name: %s\n", redir->file_name);
			add_redirect_to_command(current_cmd, redir);
		}
		else if (tokens->status->token_type == TYPE_PIPE)
		{
			if (!current_cmd || !current_cmd->cmd_name)
			{
				fprintf(stderr, "Syntax error: Pipe without command\n");
				exit(1);
			}
			current_cmd = NULL; // End current command
		}
		// else if (tokens->status->token_type == TYPE_SEMICOLON)
		// {
		// }
		else
		{
			fprintf(stderr, "Unknown token type: %d\n",
				tokens->status->token_type);
			exit(1);
		}
		tokens = tokens->next;
	}
	if (current_cmd && !current_cmd->cmd_name)
	{
		fprintf(stderr, "Syntax error: Missing command name at the end\n");
		exit(1);
	}
	return (cmd_list);
}
