/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/12 19:25:13 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAX 4096

char	*get_target_directory(char **args)
{
	char	*tag;

	tag = NULL;
	if (!args[1])
	{
		tag = getenv("HOME");
		if (!tag)
			return (fprintf(stderr, "cd: HOME not set\n"), NULL);
		tag = strdup(tag);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		tag = getenv("OLDPWD");
		if (!tag)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (NULL);
		}
		tag = strdup(tag);
	}
	else
		tag = strdup(args[1]);
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

void	change_directory(char *tag)
{
	if (!tag)
	{
		fprintf(stderr, "Error: Null target directory.\n");
		return ;
	}
	if (chdir(tag) != 0)
	{
		fprintf(stderr, "Failed to change directory to %s: ", tag);
		perror("");
		free(tag);
		return ;
	}
	free(tag);
	update_env_variables();
}

void	builtin_cd(char **av, t_shell_env *shell_env)
{
	char	*tag;

	tag = get_target_directory(av);
	if (tag)
	{
		change_directory(tag);
	}
	else
	{
		fprintf(stderr, "Error: Failed to resolve target directory.\n");
	}
	return ;
}
