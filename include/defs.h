/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/30 18:20:28 by marmulle         ###   ########.fr       */
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
}					t_vec2;

typedef struct s_vec2_int
{
	int				x;
	int				y;
}					t_vec2_int;

typedef struct s_assets
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				*floor;
	int				*ceiling;
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
	t_vec2			*side_dist;
	t_vec2			*delta_dist;
	t_vec2_int		*step_dir;
	t_vec2_int		*cell;
	bool			*is_vertical_side;
}					t_dda;

typedef struct s_player
{
	t_vec2			*pos;
	t_vec2			*dir;
	// TODO: maybe move these fields
	t_vec2			*ray_dir;
	t_vec2			*hit_pos;
	mlx_texture_t	*wall_txtr;
	t_vec2			*plane;
	t_dda			dda;
	mlx_image_t		*camera;
}					t_player;

typedef struct s_ctx
{
	mlx_t			*mlx;
	t_minimap		mini;
	t_assets		assets;
	t_map			map;
	t_player		player;
}					t_ctx;

#endif
