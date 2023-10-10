/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/10 18:38:30 by marmulle         ###   ########.fr       */
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

typedef struct s_rgb
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
}			t_rgb;

typedef struct s_assets
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	t_rgb	*floor;
	t_rgb	*ceiling;
}			t_assets;

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
void	free_2d(char **obj);

#endif
