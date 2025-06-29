/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 10:16:28 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_option_n(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

void	builtin_echo(char **args)
{
	int	i;
	int	start_index;
	int	newline_flag;

	start_index = parse_option_n(args);
	i = start_index;
	newline_flag = (start_index == 1);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline_flag)
		write(1, "\n", 1);
}

// int	main(int ac, char **av)
// {
// 	if (ac > 1)
// 	{
// 		builtin_echo(av);
// 	}
// 	else
// 		write(1, "\n", 2);
// 	return (0);
// }
