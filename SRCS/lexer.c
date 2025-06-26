/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:05:55 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 17:54:45 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**lexer(char *line)
{
	t_token	**dest;

	dest = lexer_tokenize(line);
	if (dest == NULL)
	{
		printf("malloc error\n");
		return (NULL);
	}
	if (check_token_cont(dest) > 100)
	{
		printf("too many token : this shell can use up to 100 token\n");
		fflush(stdout);
		free_all_token(dest);
		return (NULL);
	}
	lexer_set_token_vals(dest);
	// print_token(dest);
	return (dest);
}
