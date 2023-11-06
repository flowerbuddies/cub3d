/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etattevi <etattevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 19:51:08 by etattevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include "cub3d.h"

typedef void		(*t_hook)(void *);

typedef struct s_vec2
{
	double			x;
	double			y;
}					t_vec2f;

typedef struct s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct s_assets
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				*floor;
	int				*sky;
	mlx_image_t		*animated_sky[3];
}					t_assets;

typedef struct s_minimap
{
	mlx_image_t		*img;
	int				scale;
}					t_minimap;

typedef enum e_tiles
{
	_END_TILE = 0,
	FLOOR,
	WALL,
	VOID
}					t_tile;

typedef struct s_map
{
	t_tile			**tiles;
	int				height;
	int				width;
}					t_map;

typedef struct s_dda
{
	t_vec2f			*side_dist;
	t_vec2f			*delta_dist;
	t_vec2i			*step_dir;
	t_vec2i			*cell;
	bool			*is_vertical_side;
}					t_dda;

typedef struct s_player
{
	t_vec2f			*pos;
	t_vec2f			*dir;
	mlx_image_t		*camera;
	t_vec2f			*plane;
}					t_player;

typedef struct s_raycast
{
	t_vec2f			*ray_dir;
	t_vec2f			*hit_pos;
	mlx_texture_t	*wall_txtr;
	t_dda			dda;
}					t_raycast;

typedef struct s_ctx
{
	mlx_t			*mlx;
	t_minimap		mini;
	t_assets		assets;
	t_map			map;
	t_player		player;
	t_raycast		raycast;
}					t_ctx;

#endif
