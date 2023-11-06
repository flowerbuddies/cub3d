/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 17:55:08 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_ctx *ctx)
{
	ctx->raycast.ray_dir = vec2f(0, 0);
	ctx->raycast.hit_pos = vec2f(0, 0);
	ctx->raycast.dda.is_vertical_side = malloc(sizeof(bool));
	if (!ctx->raycast.dda.is_vertical_side)
		error(ctx->mlx, NULL);
	ctx->raycast.dda.cell = vec2i(0, 0);
	ctx->raycast.dda.side_dist = vec2f(0, 0);
	ctx->raycast.dda.delta_dist = vec2f(0, 0);
	ctx->raycast.dda.step_dir = vec2i(0, 0);
	ctx->player.camera = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->player.camera)
		error(ctx->mlx, NULL);
	if (mlx_image_to_window(ctx->mlx, ctx->player.camera, 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->player.camera->instances[0].z = 0;
}

static void	set_hit_pos(t_ctx *ctx, t_vec2f *pos, t_vec2f *ray_dir,
		double ray_len)
{
	ctx->raycast.hit_pos->x = pos->x + ray_dir->x * ray_len;
	ctx->raycast.hit_pos->y = pos->y + ray_dir->y * ray_len;
}

static void	set_wall_texture(t_ctx *ctx)
{
	if (*ctx->raycast.dda.is_vertical_side)
	{
		if (ctx->raycast.hit_pos->y - (double)ctx->raycast.dda.cell->y > 0.5)
			ctx->raycast.wall_txtr = ctx->assets.north;
		else
			ctx->raycast.wall_txtr = ctx->assets.south;
	}
	else
	{
		if (ctx->raycast.hit_pos->x - (double)ctx->raycast.dda.cell->x > 0.5)
			ctx->raycast.wall_txtr = ctx->assets.east;
		else
			ctx->raycast.wall_txtr = ctx->assets.west;
	}
}

static double	get_x_mapping(t_ctx *ctx)
{
	const double	delta_x
		= ctx->raycast.hit_pos->x - (double)ctx->raycast.dda.cell->x;
	const double	delta_y
		= ctx->raycast.hit_pos->y - (double)ctx->raycast.dda.cell->y;

	if (*ctx->raycast.dda.is_vertical_side)
	{
		if (delta_y > 0.5)
			return (delta_x);
		return (1 - delta_x);
	}
	else
	{
		if (delta_x > 0.5)
			return (1 - delta_y);
		return (delta_y);
	}
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
		ctx->raycast.ray_dir->x = ctx->player.dir->x + ctx->player.plane->x
			* camera_x;
		ctx->raycast.ray_dir->y = ctx->player.dir->y + ctx->player.plane->y
			* camera_x;
		ray_len = dda(ctx);
		set_hit_pos(ctx, ctx->player.pos, ctx->raycast.ray_dir, ray_len);
		set_wall_texture(ctx);
		draw_hit(ctx);
		draw_vert_strips(ctx, ray, ray_len, get_x_mapping(ctx));
	}
}
