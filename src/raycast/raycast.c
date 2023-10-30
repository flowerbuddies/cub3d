/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/30 18:30:37 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_ctx *ctx)
{
	ctx->player.ray_dir = vec2(0, 0);
	ctx->player.hit_pos = vec2(0, 0);
	ctx->player.dda.is_vertical_side = malloc(sizeof(bool));
	if (!ctx->player.dda.is_vertical_side)
		error(ctx->mlx, NULL);
	ctx->player.dda.cell = vec2_int(0, 0);
	ctx->player.dda.side_dist = vec2(0, 0);
	ctx->player.dda.delta_dist = vec2(0, 0);
	ctx->player.dda.step_dir = vec2_int(0, 0);
	ctx->player.camera = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->player.camera)
		error(ctx->mlx, NULL);
	if (mlx_image_to_window(ctx->mlx, ctx->player.camera, 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->player.camera->instances[0].z = 0;
}

static void	set_hit_pos(t_ctx *ctx, t_vec2 *pos, t_vec2 *ray_dir,
		double ray_len)
{
	ctx->player.hit_pos->x = pos->x + ray_dir->x * ray_len;
	ctx->player.hit_pos->y = pos->y + ray_dir->y * ray_len;
}

static void	draw_hit(t_ctx *ctx)
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

static int	get_texture_color(t_ctx *ctx, double width_ratio,
		double height_ratio)
{
	const int	row_length = ctx->player.wall_txtr->bytes_per_pixel
			* ctx->player.wall_txtr->width;
	const int	x_offset = row_length * width_ratio;
	const int	y_offset = ctx->player.wall_txtr->height * height_ratio;
	const int	offset = y_offset * row_length + x_offset;
	const int	r = ctx->player.wall_txtr->pixels[offset];
	const int	g = ctx->player.wall_txtr->pixels[offset + 1];
	const int	b = ctx->player.wall_txtr->pixels[offset + 2];
	const int	color = r << 24 | g << 16 | b << 8 | 0xFF;

	return (color);
}

static void	draw_vert_strips(t_ctx *ctx, int x, double ray_len,
		double width_ratio)
{
	const int	line_height = (HEIGHT / ray_len);
	int			draw_start;
	int			draw_end;
	int			color;
	double		height_ratio;

	// int			y_pixel;
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	// y_pixel = -1;
	// while (++y_pixel < draw_start) // TODO: benchmark vs clearing image.
	// 	mlx_put_pixel(ctx->player.camera, x, y_pixel, *ctx->assets.floor);
	while (draw_start < draw_end)
	{
		height_ratio = (double)(draw_start - (-line_height / 2 + HEIGHT / 2))
			/ line_height;
		color = get_texture_color(ctx, width_ratio, height_ratio);
		mlx_put_pixel(ctx->player.camera, x, draw_start++, color);
	}
	// y_pixel = draw_end;
	// while (++y_pixel < HEIGHT)
	// 	mlx_put_pixel(ctx->player.camera, x, y_pixel, *ctx->assets.ceiling);
}

static void	set_wall_texture(t_ctx *ctx)
{
	ctx->player.wall_txtr = ctx->assets.north;
}

static double	get_width_ratio(t_ctx *ctx)
{
	if (*ctx->player.dda.is_vertical_side)
		return (ctx->player.hit_pos->x - (double)ctx->player.dda.cell->x);
	else
		return (ctx->player.hit_pos->y - (double)ctx->player.dda.cell->y);
}

void	draw_raycast(t_ctx *ctx)
{
	double	ray;
	double	camera_x;
	double	ray_len;

	ray = -1;
	while (++ray < WIDTH)
	{
		camera_x = 2.0 * ray / WIDTH - 1;
		ctx->player.ray_dir->x = ctx->player.dir->x + ctx->player.plane->x
			* camera_x;
		ctx->player.ray_dir->y = ctx->player.dir->y + ctx->player.plane->y
			* camera_x;
		ray_len = dda(ctx);
		set_hit_pos(ctx, ctx->player.pos, ctx->player.ray_dir, ray_len);
		set_wall_texture(ctx);
		draw_hit(ctx);
		draw_vert_strips(ctx, ray, ray_len, get_width_ratio(ctx));
	}
}
