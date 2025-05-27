/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/27 19:44:44 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lexer(char *input, t_shell_env *shell_env_ptr)
{
	t_token **split_token;

	split_token = lexer_tokenize(input);
	if (split_token == NULL)
	{
		return (READLINE_CONTINUE);
	}
	lexer_set_token_vals(split_token); //一部expanderの内容も実装してしまった
	// marge_same_margeid_token(split_token); //これはexpanderで実装
	print_token(split_token);
	
	// print_shell_env(shell_env_ptr);
	// TODO: split_tokenのメモリ解放を実装
	
	return (READLINE_EXIT);
}

int main(int argc, char **argv, char **envp)
{
	t_shell_env *shell_env_ptr;

	shell_env_ptr = mk_shell_env(envp);
	if (shell_env_ptr == NULL)
	{
		perror("main: mk_shell_env failed");
		exit (1);
	}
	

	while (1)
	{
		char *input = readline("minishell > ");
		if (!input)
		{ // CtrlD(EOF)
			printf("exit_Ctrl_D\n");
			break;
		}
		if (*input != '\0')
		{
			while (lexer(input, shell_env_ptr) == READLINE_CONTINUE)
			{
				char *tmp = readline(" > ");
				char *concat = ft_strjoin(input, tmp);
				free(tmp);
				free(input);
				input = concat;
				//KOUBUNKAISEKI
				//continue;
			}
			add_history(input);
		}
		// rl_redisplay();
		// printf("check_input: %s\n", input);
		free(input);
	}
	return (0);
}
