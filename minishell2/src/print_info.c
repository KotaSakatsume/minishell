/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:38:16 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/15 17:43:29 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h" // t_command と関連する構造体を含むヘッダー

const char	*get_redirect_type_name(int type)
{
	if (type == REDIRECT_IN)
	{
		return ("REDIRECT_IN (<)");
	}
	else if (type == REDIRECT_OUT)
	{
		return ("REDIRECT_OUT (>)");
	}
	else if (type == REDIRECT_APPEND)
	{
		return ("REDIRECT_APPEND (>>)");
	}
	else if (type == REDIRECT_HEREDOC)
	{
		return ("REDIRECT_HEREDOC (<<)");
	}
	else
	{
		return ("UNKNOWN");
	}
}

void	print_redirect_info(t_redirect *redirect)
{
	while (redirect)
	{
		printf("  Redirect: file_name='%s', type='%s'\n", redirect->file_name,
			get_redirect_type_name(redirect->type));
		redirect = redirect->next;
	}
}

void	print_command_info(t_command *cmd)
{
	int	cmd_index;

	cmd_index = 1;
	while (cmd)
	{
		printf("Command %d:\n", cmd_index++);
		printf("  Command Name: %s\n", cmd->cmd_name ? cmd->cmd_name : "NULL");
		printf("  Arguments:\n");
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i]; i++)
			{
				printf("    - %s\n", cmd->args[i]);
			}
		}
		else
		{
			printf("    (No arguments)\n");
		}
		printf("  Redirects:\n");
		if (cmd->redirects)
		{
			print_redirect_info(cmd->redirects);
		}
		else
		{
			printf("    (No redirects)\n");
		}
		cmd = cmd->next;
		if (cmd)
		{
			printf("  |\n");
		}
	}
}
