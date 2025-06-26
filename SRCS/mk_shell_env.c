/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_shell_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:50:08 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/26 19:30:41 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	**mk_shell_env_envp(char **envp)
{
	char	**envp_ptr;
	int		i;
	int		envp_num;

	i = 0;
	envp_num = count_envp(envp);
	envp_ptr = malloc(sizeof(char *) * (envp_num + 1));
	if (envp_ptr == NULL)
	{
		perror("mk_shell_env: malloc failed");
		return (NULL);
	}
	while (i < envp_num)
	{
		envp_ptr[i] = strdup(envp[i]);
		if (envp_ptr[i] == NULL)
		{
			perror("mk_shell_env: strdup failed");
			return (NULL);
		}
		i++;
	}
	envp_ptr[i] = NULL;
	return (envp_ptr);
}

t_shell_env	*mk_shell_env(char **envp)
{
	t_shell_env	*dest;

	dest = malloc(sizeof(t_shell_env));
	if (dest == NULL)
	{
		perror("mk_shell_env: malloc failed");
		return (NULL);
	}
	dest->envp = mk_shell_env_envp(envp);
	if (dest->envp == NULL)
	{
		perror("mk_shell_env: mk_shell_env_envp failed");
		free(dest);
		return (NULL);
	}
	dest->exit_status = 0;
	return (dest);
}
