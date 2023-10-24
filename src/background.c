/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:40:48 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/24 14:24:07 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	setmem(uint8_t *pixels, int color, int32_t len)
// {
// 	int32_t	i;

// 	i = 0;
// 	while (i < len)
// 		pixels[i++] = color;
// }

// void	init_background(t_ctx *ctx)
// {
// 	const mlx_image_t	*bg = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
// 	const int32_t		halfway = sizeof(int32_t) * WIDTH * HEIGHT / 2;

// 	if (!bg)
// 		error(ctx->mlx, NULL);
// 	// ft_memset(bg->pixels, MINIMAP_WALL_COLOR, halfway);
// 	// ft_memset(bg->pixels + halfway, MINIMAP_VOID_COLOR, halfway);
// 	setmem(bg->pixels, *ctx->assets.ceiling, halfway);
// 	setmem(bg->pixels + halfway, *ctx->assets.floor, halfway);
// 	if (mlx_image_to_window(ctx->mlx, (mlx_image_t *)bg, 0, 0) == -1)
// 		error(ctx->mlx, NULL);
// 	bg->instances[0].z = -1;
// }

void init_background(t_ctx *ctx)
{
	const mlx_image_t	*bg = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	int					y;
	int					x;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel((mlx_image_t *)bg, x, y, *ctx->assets.ceiling);
	}
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel((mlx_image_t *)bg, x, y, *ctx->assets.floor);
	}
	if (mlx_image_to_window(ctx->mlx, (mlx_image_t *)bg, 0, 0) == -1)
		error(ctx->mlx, NULL);
	bg->instances[0].z = -1;
}
