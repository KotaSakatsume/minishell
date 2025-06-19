/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/19 20:37:29 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	builtin_env(char **argv, t_shell_env **head, t_shell_env *shell_env)
{
	t_env	*tmp;

	if (argv[1] != NULL)
	{
		write(2, "env: too many arguments\n", 24);
		update_exit_status(shell_env, 127);
		return ;
	}
	if (head == NULL || *head == NULL)
		return ;
	tmp = (*head)->env_list;
	while (tmp)
	{
		printf("KEY: %s, VALUE: %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	update_exit_status(shell_env, 0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	// t_env	*env_list;
// 	(void)ac;
// 	(void)av;
// 	// env_list = env_to_list(envp);
// 	// print_env_list(env_list);
// 	builtin_env(envp);
// 	return (0);
// }
