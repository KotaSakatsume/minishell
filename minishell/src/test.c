/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:16:58 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/10 11:01:45 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <readline/history.h>
// #include <readline/readline.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	main(void)
// {
// 	char	*line;

// 	rl_outstream = stderr;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (line == NULL)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		free(line);
// 	}
// 	exit(0);
// }

/*
//  * getenvの使い方サンプル
//  */
// int	main(int argc, char *argv[])
// {
// 	char	*envp;

// 	envp = getenv("PATH");
// 	printf("%s\n", envp);
// 	return (0);
// }

// #include <../include/minishell.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>

// // トークンリストの解放
// void	free_token_list(t_token *tokens)
// {
// 	t_token	*next;

// 	while (tokens)
// 	{
// 		next = tokens->next;
// 		free(tokens->value);
// 		free(tokens->status);
// 		free(tokens);
// 		tokens = next;
// 	}
// }

// // トークンリストを作成する関数（テスト用）
// t_token	*create_test_tokens(void)
// {
// 	t_token_stat	*stat1;
// 	t_token			*token1;

// 	// t_token_stat	*stat2;
// 	// t_token			*token2;
// 	// t_token_stat	*stat3;
// 	// t_token			*token3;
// 	// トークン1: "ls"
// 	stat1 = malloc(sizeof(t_token_stat));
// 	stat1->token_type = WORD; //コマンド
// 	stat1->in_quote = OUT;    //クオートなし
// 	stat1->need_expand = 0;   //
// 	stat1->after_space_is = 1;
// 	stat1->marge_id = -1;
// 	token1 = malloc(sizeof(t_token));
// 	token1->id = 1;
// 	token1->value = strdup("ls");
// 	token1->status = stat1;
// 	token1->next = NULL;
// 	// トークン2: "|"
// 	// stat2 = malloc(sizeof(t_token_stat));
// 	// stat2->token_type = PIPE;
// 	// stat2->in_quote = OUT;
// 	// stat2->need_expand = 0;
// 	// stat2->after_space_is = 1;
// 	// stat2->marge_id = -1;
// 	// token2 = malloc(sizeof(t_token));
// 	// token2->id = 2;
// 	// token2->value = strdup("|");
// 	// token2->status = stat2;
// 	// token2->next = NULL;
// 	// token1->next = token2;
// 	// // トークン3: "wc"
// 	// stat3 = malloc(sizeof(t_token_stat));
// 	// stat3->token_type = WORD;
// 	// stat3->in_quote = OUT;
// 	// stat3->need_expand = 0;
// 	// stat3->after_space_is = 1;
// 	// stat3->marge_id = -1;
// 	// token3 = malloc(sizeof(t_token));
// 	// token3->id = 3;
// 	// token3->value = strdup("wc");
// 	// token3->status = stat3;
// 	// token3->next = NULL;
// 	// token2->next = token3;
// 	// return (token1);
// }

// // コマンド実行（トークンリストから）
// void	execute_tokens(t_token *tokens)
// {
// 	int		pipe_fds[2];
// 	char	*argv[] = {tokens->value, NULL};

// 	if (!tokens)
// 	{
// 		printf("No tokens to execute.\n");
// 		return ;
// 	}
// 	int in_fd = 0; // 最初は標準入力
// 	while (tokens)
// 	{
// 		// パイプを作成
// 		if (tokens->next && tokens->status->token_type == PIPE)
// 		{
// 			pipe(pipe_fds);
// 		}
// 		else
// 		{
// 			pipe_fds[1] = 1; // 最後のコマンドは標準出力
// 		}
// 		if (fork() == 0)
// 		{
// 			// 子プロセスで実行
// 			dup2(in_fd, 0);       // 標準入力を設定
// 			dup2(pipe_fds[1], 1); // 標準出力を設定
// 			close(pipe_fds[0]);   // 読み込み側を閉じる
// 			execvp(argv[0], argv);
// 			// エラー処理
// 			perror("execvp failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			// 親プロセス
// 			wait(NULL);          // 子プロセスの終了を待つ
// 			close(pipe_fds[1]);  // 書き込み側を閉じる
// 			in_fd = pipe_fds[0]; // 次のプロセスの入力を設定
// 		}
// 		tokens = tokens->next;
// 	}
// }

// // メイン関数
// int	main(void)
// {
// 	t_token	*tokens;

// 	// テスト用トークンリストを作成
// 	tokens = create_test_tokens();
// 	// トークンを実行
// 	execute_tokens(tokens);
// 	// メモリ解放
// 	free_token_list(tokens);
// 	return (0);
// }

#include "minishell.h" // 提供された構造体のヘッダーファイル
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークン作成の補助関数
t_token	*create_token(int id, const char *value, t_token_type type,
		t_in_quote quote, int need_expand, int after_space_is)
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
	token->value = strdup(value); // 値のコピー
	token->status = status;
	status->token_type = type;
	status->in_quote = quote;
	status->need_expand = need_expand;
	status->after_space_is = after_space_is;
	status->marge_id = 0; // 初期値として 0 を設定
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
		printf("-----------------\n");
		head = head->next;
	}
	printf("==================\n");
}

int	main(void)
{
	t_token	*token1;

	// t_token	*token2;
	// t_token	*token3;
	// トークンを作成
	token1 = create_token(1, "ls", TYPE_WORD, QUOTE_OUT, 0, 1);
	// token2 = create_token(2, "|", PIPE, OUT, 0, 1);
	// token3 = create_token(3, "grep", WORD, OUT, 0, 0);
	// トークンを連結
	// token1->next = token2;
	// token2->next = token3;
	// 可視化
	visualize_tokens(token1);
	execution(token1);
	// メモリ解放
	free_tokens(token1);
	return (0);
}
