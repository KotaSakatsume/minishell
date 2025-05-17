/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:00:28 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/15 20:11:51 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_unset(char **env)
{
	
}

int	main(int ac, char **av, char **envp)
{
	t_shell_env *env;

	(void)ac;
	(void)av;
	env->envp = envp;
	env->exit_status = 0;
	built_in_unset(env->envp);
	return (0);
}
