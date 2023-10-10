/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/10 19:28:04 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include "libft.h"

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
	mlx_image_t	*image;
	const int	width;
	const int	height;
}				t_minimap;

typedef struct s_ctx
{
	mlx_t		*mlx;
	t_assets	assets;
	t_minimap	mini;

}				t_ctx;

int		error(mlx_t *mlx, char *message);
void	parse(char *filename, t_assets *assets);
int		open_file(char *filename);
bool	streq(const char *s1, const char *s2);
void	free_2d(const char **obj);
int		len_2d(const char **obj);
void	parse_params(int fd, t_assets *assets);

#endif
