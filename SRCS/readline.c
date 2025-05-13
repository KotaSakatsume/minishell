/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:23 by mkuida            #+#    #+#             */
/*   Updated: 2025/05/07 16:51:38 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int lexer(char *input)
{
	char** split_token;
	static t_token** head_pp = NULL;

	if(head_pp == NULL)
	{
		head_pp = malloc(sizeof(t_token*));
		if(head_pp == NULL)
		{
			printf ("lexer : malloc\n");
			return (1);
		}
		*head_pp = NULL;
	}
	split_token = lexer_split(input);
	if(split_token == NULL)
	{
		//freetyekku
		printf ("lexer_split : malloc\n");
		return (1);
	}
	cnv_splited_to_stoken(split_token, head_pp);
	return (0);
}


int	main(void)
{
	while (1)
	{
		char *input = readline("minishell > ");
		if (!input)
		{ // CtrlD(EOF)
			printf("exit\n");
			break ;
		}
		if (*input != '\0')
		{
			lexer(input);
			add_history(input);
		}
		// rl_redisplay();
		// printf("check_input: %s\n", input);
		free(input);
	}
	return (0);
}
