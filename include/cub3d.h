/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 19:43:03 by hunam            ###   ########.fr       */
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
	VOID,
	_END_TILE
}					t_tile;

typedef struct s_map
{
	t_tile			**tiles;
	int				height;
	int				width;
}					t_map;

typedef struct s_ctx
{
	mlx_t			*mlx;
	t_assets		assets;
	t_minimap		mini;
	t_map			map;

}					t_ctx;

typedef struct s_free
{
	void			(*params)(void);
	void			(*map)(void);
}					t_free;

// main.c
t_ctx				*get_ctx(void);

// utils.c
int					len_2d(const char **obj);
bool				streq(const char *s1, const char *s2);
int					open_file(char *filename);
char				*gnl_no_nl(int fd);

// error.c
void				error(mlx_t *mlx, char *message);

// free.c
void				free_2d(const char **obj);
t_free				*free_the(void);

// parser/*.c
void				parse(char *filename, t_ctx *ctx);
void				parse_params(int fd, t_assets *assets);
void				parse_map(int fd, t_map *map);
void				check_map_validity(t_map *map);

#endif
