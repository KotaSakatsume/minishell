/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/19 18:58:17 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_exit(char **av)
{
	int	i;

	i = 0;
	if (strcmp(av[1], "exit") == 0)
	{
		printf("OK\n");
		return ;
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 1)
		handle_exit(av);
	return (0);
}
