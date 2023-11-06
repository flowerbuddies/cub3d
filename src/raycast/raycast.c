/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 14:39:58 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_ctx *ctx)
{
	ctx->player.ray_dir = vec2f(0, 0);
	ctx->player.hit_pos = vec2f(0, 0);
	ctx->player.dda.is_vertical_side = malloc(sizeof(bool));
	if (!ctx->player.dda.is_vertical_side)
		error(ctx->mlx, NULL);
	ctx->player.dda.cell = vec2i(0, 0);
	ctx->player.dda.side_dist = vec2f(0, 0);
	ctx->player.dda.delta_dist = vec2f(0, 0);
	ctx->player.dda.step_dir = vec2i(0, 0);
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
	ctx->player.hit_pos->x = pos->x + ray_dir->x * ray_len;
	ctx->player.hit_pos->y = pos->y + ray_dir->y * ray_len;
}

static void	set_wall_texture(t_ctx *ctx)
{
	if (*ctx->player.dda.is_vertical_side)
	{
		if (ctx->player.hit_pos->y - (double)ctx->player.dda.cell->y > 0.5)
			ctx->player.wall_txtr = ctx->assets.north;
		else
			ctx->player.wall_txtr = ctx->assets.south;
	}
	else
	{
		if (ctx->player.hit_pos->x - (double)ctx->player.dda.cell->x > 0.5)
			ctx->player.wall_txtr = ctx->assets.east;
		else
			ctx->player.wall_txtr = ctx->assets.west;
	}
}

static double	get_x_mapping(t_ctx *ctx)
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
		draw_vert_strips(ctx, ray, ray_len, get_x_mapping(ctx));
	}
}
