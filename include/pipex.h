/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:16:58 by kosakats          #+#    #+#             */
/*   Updated: 2025/04/08 16:40:11 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <aio.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_file
{
	char	*infile;
	char	*outfile;
	int		cmd_count;
}			t_file;

char		*find_path(char *cmd, char **envp);
void		execute(char *argv, char **envp);
void		first_child_process(t_file *file, char *cmd, int *pipe_fd,
				char **envp);
void		middle_child_process(char *cmd, int *pipe_fd, int *old_pipe_fd,
				char **envp);
void		last_child_process(t_file *file, char *cmd, int *old_pipe_fd,
				char **envp);
void		error(void);
#endif