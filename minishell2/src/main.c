/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:01:03 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/16 18:46:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // 提供された構造体のヘッダーファイル
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークン作成の補助関数
t_token	*create_token(int id, const char *value, t_token_type type,
		t_in_quote quote, int need_expand, int after_space_is,
		int token_marge_id)
{
	t_token			*token;
	t_token_stat	*status;

	token = malloc(sizeof(t_token));
	status = malloc(sizeof(t_token_stat));
	if (!token || !status)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	token->id = id;
	token->value = strdup(value);           // 値のコピー
	token->token_marge_id = token_marge_id; // 初期値として 0 を設定
	token->status = status;
	status->token_type = type;
	status->in_quote = quote;
	status->need_expand = need_expand;
	status->after_space_is = after_space_is;
	token->next = NULL;
	return (token);
}

// トークンリストの解放
void	free_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token->status);
		free(token);
		token = next;
	}
}

// 単体テスト関数
// void	test_token_structure(void)
// {
// 	t_token	*token1;
// 	t_token	*token2;
// 	t_token	*token3;

// 	// トークンを1つ作成
// 	token1 = create_token(1, "echo", WORD, OUT, 0, 1);
// 	assert(token1->id == 1);
// 	assert(strcmp(token1->value, "echo") == 0);
// 	assert(token1->status->token_type == WORD);
// 	assert(token1->status->in_quote == OUT);
// 	assert(token1->status->need_expand == 0);
// 	assert(token1->status->after_space_is == 1);
// 	// トークンを連結してリストを作成
// 	token2 = create_token(2, "|", PIPE, OUT, 0, 1);
// 	token1->next = token2;
// 	token3 = create_token(3, "grep", WORD, OUT, 0, 0);
// 	token2->next = token3;
// 	// リストをテスト
// 	assert(token1->next == token2);
// 	assert(token2->next == token3);
// 	assert(token3->next == NULL);
// 	// 各トークンの値をテスト
// 	assert(strcmp(token2->value, "|") == 0);
// 	assert(token3->status->token_type == WORD);
// 	assert(strcmp(token3->value, "grep") == 0);
// 	printf("All tests passed for token structure!\n");
// 	// メモリ解放
// 	free_tokens(token1);
// }

// メイン関数

// トークンタイプの名前を返すヘルパー関数
const char	*get_token_type_name(t_token_type type)
{
	switch (type)
	{
	case TYPE_WORD:
		return ("TYPE_WORD");
	case TYPE_PIPE:
		return ("TYPE_PIPE");
	case TYPE_REDIRECT_IN:
		return ("TYPE_REDIRECT_IN");
	case TYPE_REDIRECT_OUT:
		return ("TYPE_REDIRECT_OUT");
	case TYPE_REDIRECT_APPEND:
		return ("TYPE_REDIRECT_APPEND");
	case TYPE_REDIRECT_HEREDOC:
		return ("TYPE_REDIRECT_HEREDOC");
	case TYPE_QUOTE_SINGLE:
		return ("TYPE_QUOTE_SINGLE");
	case TYPE_QUOTE_DOUBLE:
		return ("TYPE_QUOTE_DOUBLE");
	case TYPE_SEMICOLON:
		return ("TYPE_SEMICOLON");
	case TYPE_EOF:
		return ("TYPE_EOF");
	default:
		return ("UNKNOWN");
	}
}

// クオート状態の名前を返すヘルパー関数
const char	*get_quote_state_name(t_in_quote quote)
{
	switch (quote)
	{
	case QUOTE_OUT:
		return ("QUOTE_OUT");
	case QUOTE_SINGLE:
		return ("QUOTE_SINGLE");
	case QUOTE_DOUBLE:
		return ("QUOTE_DOUBLE");
	default:
		return ("UNKNOWN");
	}
}

// リスト内容の可視化関数
void	visualize_tokens(t_token *head)
{
	printf("=== Token List ===\n");
	while (head)
	{
		printf("ID: %d\n", head->id);
		printf("Value: %s\n", head->value);
		printf("Type: %s\n", get_token_type_name(head->status->token_type));
		printf("Quote: %s\n", get_quote_state_name(head->status->in_quote));
		printf("Need Expand: %s\n", head->status->need_expand ? "Yes" : "No");
		printf("After Space: %s\n",
			head->status->after_space_is ? "Yes" : "No");
		printf("Token Marge ID: %d\n", head->token_marge_id);
		printf("-----------------\n");
		head = head->next;
	}
	printf("==================\n");
}

int	main(int ac, char **av, char **envp)
{
	t_shell_env	*shell_env;
	t_token		*token1;
	t_token		*token2;
	t_token		*token3;
	t_token		*token4;
	t_token		*token5;

	// t_token		*token6;
	// t_token		*token7;
	shell_env = malloc(sizeof(t_shell_env));
	if (!shell_env)
	{
		perror("Failed to allocate memory for shell_env");
		return (EXIT_FAILURE);
	}
	shell_env->envp = envp;
	shell_env->exit_status = 0;
	(void)ac;
	(void)av;
	// トークンを作成
	token1 = create_token(1, "ls", TYPE_WORD, QUOTE_OUT, 0, 1, 0);
	token2 = create_token(2, "|", TYPE_PIPE, QUOTE_OUT, 0, 1, 1);
	token3 = create_token(3, "grep", TYPE_WORD, QUOTE_OUT, 0, 0, 2);
	token4 = create_token(4, "|", TYPE_PIPE, QUOTE_OUT, 0, 1, 3);
	token5 = create_token(1, "ls", TYPE_WORD, QUOTE_OUT, 0, 1, 4);
	// token6 = create_token(5, ">", TYPE_REDIRECT_IN, QUOTE_OUT, 0, 1, 5);
	// token7 = create_token(6, "out", TYPE_WORD, QUOTE_OUT, 0, 1, 6);
	// token2 = create_token(1, "\"hello\"", TYPE_WORD, QUOTE_OUT, 0, 1, 1);
	// token3 = create_token(1, "\"world\"", TYPE_WORD, QUOTE_OUT, 0, 1, 2);
	// token4 = create_token(1, "ls", TYPE_WORD, QUOTE_OUT, 0, 1, 2);
	// トークンを連結
	token1->next = token2;
	token2->next = token3;
	token3->next = token4;
	token4->next = token5;
	// token5->next = token6;
	// token6->next = token7;
	// 可視化
	visualize_tokens(token1);
	execution_minishell(token1, shell_env);
	// メモリ解放
	free_tokens(token1);
	free(shell_env);
	return (0);
}
