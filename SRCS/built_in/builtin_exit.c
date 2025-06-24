/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/19 17:07:45 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_EXIT_STATUS 255

// 引数の検証
void	print_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

int	validate_exit_arguments(char **args)
{
	int	i;

	i = 0;
	// 引数がない場合
	if (args[1] == NULL)
		return (0);
	// 引数が数値か確認
	while (args[1][i])
	{
		if (!((args[1][i] >= '0' && args[1][i] <= '9') || (args[1][0] == '-')))
		{
			print_error("exit: ");
			print_error(args[1]);
			print_error(": numeric argument required\n");
			return (2);
		}
		i++;
	}
	// 引数が多すぎる場合
	if (args[2] != NULL)
	{
		print_error("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

// 数値引数の変換
int	convert_exit_status(char *arg)
{
	long	status;

	status = strtol(arg, NULL, 10);
	// 負数や範囲外の値を調整
	if (status < 0)
		return (256 + (status % 256));
	return (status % 256);
}

// プログラム終了
void	execute_exit(int exit_status)
{
	printf("exit\n");
	exit(exit_status);
}

// メインの exit 処理
void	builtin_exit(char **args)
{
	int	validation_result;
	int	exit_status;

	// 引数を検証
	validation_result = validate_exit_arguments(args);
	if (validation_result == 1) // 引数が多すぎる
		return ;
	if (validation_result == 2) // 数値でない引数
		execute_exit(2);
	// 引数が数値の場合、終了ステータスを計算
	if (args[1])
	{
		exit_status = convert_exit_status(args[1]);
		printf("exit_status: %d\n", exit_status);
	}
	else
		exit_status = 0;
	// プログラムを終了
	execute_exit(exit_status);
}

// テスト用メイン関数
// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 		handle_exit(argv);
// 	return (0);
// }
