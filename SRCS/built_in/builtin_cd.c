/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/28 16:50:12 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAX 4096

char	*get_target_directory(char **args, t_env *env_list)
{
	char	*tag;
	t_env	*tmp_list;

	tag = NULL;
	tmp_list = env_list;
	if (!args[1])
	{
		while (tmp_list)
		{
			if (ft_strcmp(tmp_list->key, "HOME") == 0)
			{
				tag = getenv("HOME");
				tag = ft_strdup(tag);
			}
			tmp_list = tmp_list->next;
		}
		if (!tag)
			return (write(2, "cd: HOME not set\n", 17), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		while (tmp_list)
		{
			if (ft_strcmp(tmp_list->key, "OLDPWD") == 0)
			{
				tag = getenv("OLDPWD");
				tag = ft_strdup(tag);
			}
			tmp_list = tmp_list->next;
		}
		if (!tag)
			return (write(2, "cd: OLDPWD not set\n", 19), NULL);
	}
	else
		tag = ft_strdup(args[1]);
	return (tag);
}

void	update_env_variables(void)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd failed");
		return ;
	}
	old_pwd = getenv("PWD");
	if (old_pwd)
	{
		if (setenv("OLDPWD", old_pwd, 1) != 0)
		{
			perror("Failed to update OLDPWD");
			return ;
		}
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("Failed to update PWD");
		return ;
	}
}

int	change_directory(char *tag)
{
	if (!tag)
	{
		write(2, "Error: Null target directory.\n", 30);
		return (1);
	}
	if (chdir(tag) != 0)
	{
		// fprintf(stderr, "Failed to change directory to %s: ", tag);
		write(2, "Failed to change directory to ", 30);
		write(2, tag, ft_strlen(tag));
		write(2, ":", 1);
		perror("");
		free(tag);
		return (1);
	}
	free(tag);
	update_env_variables();
	return (0);
}

void	builtin_cd(char **av, t_shell_env *shell_env)
{
	char	*tag;
	int		status;

	if (av[2] == NULL)
	{
		tag = get_target_directory(av, shell_env->env_list);
		if (tag)
		{
			status = change_directory(tag);
			update_exit_status(shell_env, status);
		}
		else
		{
			write(2, "Error: Failed to resolve target directory.\n", 43);
			update_exit_status(shell_env, 1);
		}
	}
	else
		write(2, "bash: cd: too many arguments\n", 29);
	return ;
}
