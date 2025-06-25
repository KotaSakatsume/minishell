/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:23:04 by mkuida            #+#    #+#             */
/*   Updated: 2025/06/25 11:12:00 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expander(t_job *job_head, t_shell_env *t_shellenv_ptr)
{
	fx_extend_to_all_pipeline_with_env(job_head , t_shellenv_ptr , extend_daller);
	printf("1");
	fx_extend_to_all_pipeline(job_head , delete_quote_cmd);
	printf("2");
	fx_extend_to_all_pipeline(job_head , combine_main);
	printf("3");
	exchange_token_to_char(job_head);
	printf("4");
}
