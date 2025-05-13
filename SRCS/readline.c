/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/13 18:00:36 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lexer(char *input)
{
	t_token **split_token;

	split_token = lexer_tokenize(input);
	if (split_token == NULL)
	{
		perror("lexer: tokenize failed");
		return (1);
	}
	set_token_vals(split_token);
	print_token(split_token);
	// TODO: split_tokenのメモリ解放を実装
	return (0);
}

int main(void)
{
	while (1)
	{
		char *input = readline("minishell > ");
		if (!input)
		{ // CtrlD(EOF)
			printf("exit\n");
			break;
		}
		if (*input != '\0')
		{
			if (lexer(input) != 0)
			{
				free(input);
				continue;
			}
			add_history(input);
		}
		// rl_redisplay();
		// printf("check_input: %s\n", input);
		free(input);
	}
	return (0);
}
