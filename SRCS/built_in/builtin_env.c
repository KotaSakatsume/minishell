/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/10 18:35:44 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_env(t_shell_env **head)
{
    if (head == NULL || *head == NULL)
        return;
    t_env *tmp = (*head)->env_list;
    while (tmp)
    {
        printf("KEY: %s, VALUE: %s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
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
