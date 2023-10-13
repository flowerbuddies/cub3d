/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 13:51:09 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

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
	mlx_image_t		*image;
	const int		width;
	const int		height;
}					t_minimap;

typedef enum e_tiles
{
	FLOOR,
	WALL,
	PLAYER,
	BOUNDS,
	_END_TILE
}	t_tile;

typedef struct s_map
{
	t_tile		**tilemap;
	int			height;
	int			width;
}				t_map;

typedef struct s_ctx
{
	mlx_t			*mlx;
	t_assets		assets;
	t_minimap		mini;
	t_map			map;

}					t_ctx;

// utils.c
int					len_2d(const char **obj);
bool				streq(const char *s1, const char *s2);
int					open_file(char *filename);
void				error(mlx_t *mlx, char *message);
char				*gnl_no_nl(int fd);

// free.c
void				free_2d(const char **obj);
void				free_assets(t_assets *assets);
void				free_map(t_map *map);

// parser/*.c
void				parse(char *filename, t_ctx *ctx);
void				parse_params(int fd, t_assets *assets);
void				parse_map(int fd, t_map *map);
void				check_map_validity(t_map *map);

#endif
