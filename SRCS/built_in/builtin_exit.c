/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 12:44:41 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_EXIT_STATUS 255

static void	ft_print_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

int	validate_exit_arguments(char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		return (0);
	while (args[1][i])
	{
		if (!((args[1][i] >= '0' && args[1][i] <= '9') || (args[1][0] == '-')))
		{
			ft_print_error("exit: ");
			ft_print_error(args[1]);
			ft_print_error(": numeric argument required\n");
			return (2);
		}
		i++;
	}
	if (args[2] != NULL)
	{
		ft_print_error("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	convert_exit_status(char *arg)
{
	long	status;
	int		sign;
	size_t	i;

	status = 0;
	sign = 1;
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		status = status * 10 + (arg[i] - '0');
		if (status > LONG_MAX)
			break ;
		i++;
	}
	status *= sign;
	if (status < 0)
		return (256 + (status % 256));
	return (status % 256);
}

void	execute_exit(int exit_status)
{
	printf("exit\n");
	exit(exit_status);
}

void	builtin_exit(char **args)
{
	int	validation_result;
	int	exit_status;

	validation_result = validate_exit_arguments(args);
	if (validation_result == 1)
		return ;
	if (validation_result == 2)
		execute_exit(2);
	if (args[1])
	{
		exit_status = convert_exit_status(args[1]);
		// printf("exit_status: %d\n", exit_status);
	}
	else
		exit_status = 0;
	execute_exit(exit_status);
}

// テスト用メイン関数
// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 		handle_exit(argv);
// 	return (0);
// }
