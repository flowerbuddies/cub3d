/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:40:48 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/24 14:39:27 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_pixels_color(uint8_t *pixels, int color, int32_t len)
{
	int32_t	i;

	i = 0;
	while (i < len)
	{
		pixels[i++] = (uint8_t)(color >> 24);
		pixels[i++] = (uint8_t)(color >> 16);
		pixels[i++] = (uint8_t)(color >> 8);
		pixels[i++] = (uint8_t)(color & 0xFF);
	}
}

void	init_background(t_ctx *ctx)
{
	const mlx_image_t	*bg = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	const int32_t		halfway = sizeof(int32_t) * WIDTH * HEIGHT / 2;

	if (!bg)
		error(ctx->mlx, NULL);
	set_pixels_color(bg->pixels, *ctx->assets.ceiling, halfway);
	set_pixels_color(bg->pixels + halfway, *ctx->assets.floor, halfway);
	if (mlx_image_to_window(ctx->mlx, (mlx_image_t *)bg, 0, 0) == -1)
		error(ctx->mlx, NULL);
	bg->instances[0].z = -1;
}
