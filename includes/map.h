/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:59:44 by mkuida            #+#    #+#             */
/*   Updated: 2025/04/21 18:09:47 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef enum e_map_type
{
	EMPTY,
	WALL,
	COLLECTIBLE,
	PLAYER,
	EXIT,
}					t_floor_state;

typedef struct s_point
{
	int				x;
	int				y;
	t_floor_state	floor_type;
}					t_point;

typedef struct s_map
{
	t_point			**contents;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
	int				collectible_count_current;
	int				collectible_count_total;
	char			*map_path;
}					t_map;

typedef struct s_xy
{
	int				x;
	int				y;
}					t_xy;

#endif