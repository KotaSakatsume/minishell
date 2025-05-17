/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/15 20:12:00 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell_env	*env;

	(void)ac;
	(void)av;
	env->envp = envp;
	env->exit_status = 0;
	built_in_env(env->envp);
	return (0);
}
