/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/10 15:21:22 by kosakats         ###   ########.fr       */
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
				return (1); // `-n` 以外の文字が含まれる場合終了
			}
			j++;
		}
		i++;
	}
	return (i); // オプション以外の引数の開始インデックスを返す
}

void	builtin_echo(char **args)
{
	int	i;
	int	start_index;
	int	newline_flag;

	// printf("OK\n");
	start_index = parse_option_n(args); // オプション解析
	i = start_index;
	newline_flag = (start_index == 1); // `-n` がなければ改行フラグをオン
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline_flag)
		write(1, "\n", 1); // 改行フラグがオンの場合のみ改行を出力
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
