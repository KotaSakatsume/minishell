/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:14:06 by mkuida            #+#    #+#             */
/*   Updated: 2025/04/16 17:41:12 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# ifndef MAP_H
#  include "map.h"
#  define MAP_H
# endif

typedef struct s_queue_point
{
	int						x;
	int						y;
	struct s_queue_point	*next;
}							t_queue_point;

typedef struct s_queue
{
	t_queue_point			*top;
	t_queue_point			*tail;
}							t_queue;

#endif