/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/29 11:43:24 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAX 4096

void	update_env_variable(char *key, char *value, t_env **env_list)
{
	t_env	*node;
	t_env	*new_node;

	node = *env_list;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env_list;
	*env_list = new_node;
}

void	update_env_variables(t_env **env_list)
{
	char	cwd[PATH_MAX];
	t_env	*pwd_node;
	char	*old_pwd;

	old_pwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd failed");
		return ;
	}
	pwd_node = *env_list;
	while (pwd_node)
	{
		if (ft_strcmp(pwd_node->key, "PWD") == 0)
		{
			old_pwd = ft_strdup(pwd_node->value);
			break ;
		}
		pwd_node = pwd_node->next;
	}
	if (old_pwd)
		update_env_variable("OLDPWD", old_pwd, env_list);
	free(old_pwd);
	update_env_variable("PWD", cwd, env_list);
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*node;

	node = env_list;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (NULL);
}

char	*get_target_directory(char **args, t_env *env_list)
{
	char	*tag;

	if (!args[1])
	{
		tag = get_env_value(env_list, "HOME");
		if (!tag)
		{
			write(2, "cd: HOME not set\n", 17);
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		tag = get_env_value(env_list, "OLDPWD");
		if (!tag)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
	}
	else
		tag = ft_strdup(args[1]);
	return (tag);
}

int	change_directory(char *tag, t_env **env_list)
{
	if (!tag)
	{
		write(2, "Error: Null target directory.\n", 30);
		return (1);
	}
	if (chdir(tag) != 0)
	{
		write(2, "Failed to change directory to ", 30);
		write(2, tag, ft_strlen(tag));
		write(2, ":", 1);
		perror("");
		free(tag);
		return (1);
	}
	free(tag);
	update_env_variables(env_list);
	return (0);
}

void	builtin_cd(char **av, t_shell_env *shell_env)
{
	char	*tag;
	int		status;

	if (!av[1] || av[2] == NULL)
	{
		tag = get_target_directory(av, shell_env->env_list);
		if (tag)
		{
			status = change_directory(tag, &shell_env->env_list);
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
}
