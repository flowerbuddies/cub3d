/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/19 16:09:22 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tiles_len(t_tile *tiles)
{
	int	i;

	i = 0;
	while (*tiles++)
		i++;
	return (i);
}

void	init_raycast(t_ctx *ctx)
{
	ctx->player.plane = vec2(0.0, 0.7);
	ctx->player.dda.side = vec2(0.0, 0.0);
	ctx->player.dda.delta = vec2(0.0, 0.0);
	ctx->player.dda.step = vec2_int(0, 0);
	ctx->player.dda.cell = vec2_int(0, 0);
}

static double	dda(t_ctx *ctx, t_vec2 *ray_dir)
{
	int		cell_x;
	int		cell_y;
	t_vec2	*side_dist;
	t_vec2	*delta_dist;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	bool	is_vertical_side;

	// t_vec2	*step;
	// TODO: malloc all vecs once, reinit values
	// map_cell = vec2(ctx->player.pos->x, ctx->player.pos->y);
	cell_x = ctx->player.pos->x;
	cell_y = ctx->player.pos->y;
	side_dist = vec2(0, 0);
	delta_dist = vec2(BIG_DOUBLE, BIG_DOUBLE);
	if (ray_dir->x != 0)
		delta_dist->x = fabs(1 / ray_dir->x);
	if (ray_dir->y != 0)
		delta_dist->y = fabs(1 / ray_dir->y);
	// step = vec2(0, 0);
	is_vertical_side = false;
	//
	if (ray_dir->x < 0)
	{
		step_x = -1.0;
		side_dist->x = (ctx->player.pos->x - cell_x) * delta_dist->x;
	}
	else
	{
		step_x = 1.0;
		side_dist->x = (cell_x + 1.0 - ctx->player.pos->x) * delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		step_y = -1.0;
		side_dist->y = (ctx->player.pos->y - cell_y) * delta_dist->y;
	}
	else
	{
		step_y = 1.0;
		side_dist->y = (cell_y + 1.0 - ctx->player.pos->y) * delta_dist->y;
	}
	// cool separator
	// have max_iteration for safety
	while (42)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			cell_x += step_x;
			is_vertical_side = false;
		}
		else
		{
			side_dist->y += delta_dist->y;
			cell_y += step_y;
			is_vertical_side = true;
		}
		// TODO: care about _END_TILE
		if (cell_y < ctx->map.height
			&& cell_x < tiles_len(ctx->map.tiles[(int)cell_y])
			&& ctx->map.tiles[(int)cell_y][(int)cell_x] == WALL)
			break ;
	}
	if (!is_vertical_side)
		perp_wall_dist = (side_dist->x - delta_dist->x);
	else
		perp_wall_dist = (side_dist->y - delta_dist->y);
	return (perp_wall_dist);
}

t_vec2	*get_hit_pos(t_vec2 *pos, t_vec2 *ray_dir, double ray_len)
{
	return (vec2(pos->x + ray_dir->x * ray_len, pos->y + ray_dir->y * ray_len));
}

static void	draw_hit(t_ctx *ctx, t_vec2 *ray_dir, double ray_len)
{
	const t_vec2	*hit_pos = get_hit_pos(ctx->player.pos, ray_dir, ray_len);
	const int		hit_size = ctx->mini.scale >> 3;
	int				y;
	int				x;

	y = -hit_size;
	while (++y < hit_size)
	{
		x = -hit_size;
		while (++x < hit_size)
			mlx_put_pixel(ctx->mini.img, (int)(hit_pos->x * ctx->mini.scale)
				+ x, (int)(hit_pos->y * ctx->mini.scale) + y, 0x00FF00FF);
	}
}

void	raycast(t_ctx *ctx)
{
	const double	max_rays = 100;
	double			ray;
	double			camera_x;
	t_vec2			*ray_dir;
	double			ray_len;

	ray = -1;
	ray_dir = vec2(0, 0);
	while (++ray < max_rays)
	{
		camera_x = (2.0 * ray / max_rays) - 1;
		ray_dir->x = ctx->player.dir->x + ctx->player.plane->x * camera_x;
		ray_dir->y = ctx->player.dir->y + ctx->player.plane->y * camera_x;
		ray_len = dda(ctx, ray_dir);
		draw_hit(ctx, ray_dir, ray_len);
	}
	free(ray_dir);
}
