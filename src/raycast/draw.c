/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:26:00 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 14:26:43 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hit(t_ctx *ctx)
{
	const int	hit_size = ctx->mini.scale / 4;
	int			y;
	int			x;

	y = -hit_size;
	while (++y < hit_size)
	{
		x = -hit_size;
		while (++x < hit_size)
			mlx_put_pixel(ctx->mini.img, ctx->player.hit_pos->x
				* ctx->mini.scale + x, ctx->player.hit_pos->y * ctx->mini.scale
				+ y, MINIMAP_WALL_COLOR * 2);
	}
}

static int	get_texture_color(t_ctx *ctx, double x_mapping, double y_mapping)
{
	const int	x_offset = ctx->player.wall_txtr->width * x_mapping;
	const int	y_offset = ctx->player.wall_txtr->height * y_mapping;
	const int	offset = x_offset * ctx->player.wall_txtr->bytes_per_pixel
		+ y_offset * ctx->player.wall_txtr->bytes_per_pixel
		* ctx->player.wall_txtr->width;
	const int	color = ctx->player.wall_txtr->pixels[offset] << 24
		| ctx->player.wall_txtr->pixels[offset + 1] << 16
		| ctx->player.wall_txtr->pixels[offset + 2] << 8
		| 0xFF;

	return (color);
}

void	draw_vert_strips(t_ctx *ctx, int x, double ray_len,
		double x_mapping)
{
	const int	line_height = (HEIGHT / ray_len);
	int			y_strip;
	int			end_y_strip;
	double		y_mapping;

	y_strip = -line_height / 2 + HEIGHT / 2;
	if (y_strip < 0)
		y_strip = 0;
	end_y_strip = line_height / 2 + HEIGHT / 2;
	if (end_y_strip >= HEIGHT)
		end_y_strip = HEIGHT - 1;
	while (y_strip < end_y_strip)
	{
		y_mapping = (double)(y_strip - (-line_height / 2 + HEIGHT / 2))
			/ line_height;
		mlx_put_pixel(ctx->player.camera, x, y_strip++,
			get_texture_color(ctx, x_mapping, y_mapping));
	}
}
