/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etattevi <etattevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:40:48 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 22:04:50 by etattevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_half(mlx_image_t *img, int color)
{
	size_t	i;

	i = 0;
	while (i < sizeof(int32_t) * WIDTH * HEIGHT / 2)
	{
		img->pixels[i++] = (uint8_t)(color >> 24);
		img->pixels[i++] = (uint8_t)(color >> 16);
		img->pixels[i++] = (uint8_t)(color >> 8);
		img->pixels[i++] = (uint8_t)(color & 0xFF);
	}
}

static void	draw_floor(t_ctx *ctx)
{
	mlx_image_t	*floor;

	floor = mlx_new_image(ctx->mlx, WIDTH, HEIGHT / 2);
	draw_half(floor, *ctx->assets.floor);
	if (mlx_image_to_window(ctx->mlx, (mlx_image_t *)floor, 0, HEIGHT / 2) == -1)
		error(ctx->mlx, NULL);
	floor->instances[0].z = -1;
}

void	init_background(t_ctx *ctx)
{
	draw_floor(ctx);
	if (*ctx->assets.sky == BLACK)
		return (init_animated_sky(ctx));
	draw_static_sky(ctx);
}
