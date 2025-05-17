/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:51 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/17 16:28:13 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_export
{
	char	*key;
	char	*value;
}			t_export;

typedef struct s_env
{
	char *key;          // 環境変数のキー
	char *value;        // 環境変数の値
	struct s_env *next; // 次のノード
}			t_env;

void	split_key_value(char *str, t_export *export)
{
	char	**ans;
	char	*str_buf;

	str_buf = str;
	while (*str)
	{
		if (*str == '=')
		{
			str++;
			if (*str == '\0')
			{
				ans = ft_split(str_buf, '=');
				export->key = strdup(ans[0]);
				export->value = strdup("");
				for (int i = 0; ans[i]; i++)
					free(ans[i]);
				free(ans);
				return ;
			}
			else
			{
				ans = ft_split(str_buf, '=');
				export->key = strdup(ans[0]);
				export->value = strdup(ans[1]);
				for (int i = 0; ans[i]; i++)
					free(ans[i]);
				free(ans);
				return ;
			}
		}
		str++;
	}
	export->key = strdup(str_buf);
	export->value = NULL;
}

void	is_valid_key(t_export *export)
{
	char	*current;

	printf("Key: %s\nValue: %s\n", export->key, export->value);
	current = export->key;
	if (!((*current >= 'A' && *current <= 'Z') || (*current >= 'a'
				&& *current <= 'z') || (*current == '_')))
	{
		printf("Error\n");
	}
	current++;
	while (*current)
	{
		if (!((*current >= 'A' && *current <= 'Z') || (*current >= 'a'
					&& *current <= 'z') || (*current >= '0' && *current <= '9')
				|| (*current == '_')))
		{
			printf("Error\n");
		}
		current++;
	}
}

int	find_env_key(t_export *export, char **env)
{
	int	i;

	i = 0;
	ft_strjoin(export->key, "=");
	printf("export->key: %s\n", export->key);
	// while (env[i])
	// {
	// 	if (ft_strnstr(env[i], export->key, ft_strlen(export->key)) == 0)
	// 	// printf("test\n");
	// 	{
	// 		return (0);
	// 	}
	// 	i++;
	// }
	// if (env[i] == NULL)
	// 	return (1);
	// while (env)
	// {
	// 	if (strncmp)
	// 		env++;
	// }
	return (0);
}

void	update_or_add_env(t_export *export, char **env)
{
	// if (find_env_key(export, env) == 1)
	// {
	// 	printf("1\n");
	// 	return ;
	// }
	// printf("2\n");
	// return ;
	export->key = ft_strjoin(export->key, "=");
	printf("export->key: %s\n", export->key);
}

void	builtin_export(char *str, char **env)
{
	t_export	*export;

	export = malloc(sizeof(t_export));
	if (!export)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return ;
	}
	export->key = NULL;
	export->value = NULL;
	split_key_value(str, export);
	printf("Key: %s\nValue: %s\n", export->key, export->value);
	is_valid_key(export);
	update_or_add_env(export, env);
	free(export->key);
	if (export->value)
		free(export->value);
	free(export);
}

int	main(int ac, char **av, char **envp)
{
	t_shell_env	*shell_env;
	t_env		*env_list;

	shell_env = malloc(sizeof(t_shell_env));
	if (!shell_env)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	shell_env->envp = envp;
	shell_env->exit_status = 0;
	// 環境変数を連結リストに変換
	env_list = env_to_list(envp);
	// 連結リストを出力
	print_env_list(env_list);
	// if (ac > 1)
	// 	builtin_export(av[1], shell_env->envp);
	// free(shell_env);
	return (0);
}
