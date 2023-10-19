/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/19 17:01:04 by marmulle         ###   ########.fr       */
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
	const t_dda	*dda = &(ctx->player.dda);
	double		perp_wall_dist;
	bool		is_vertical_side;

	dda->cell->x = ctx->player.pos->x;
	dda->cell->y = ctx->player.pos->y;
	dda->side->x = 0.0;
	dda->side->y = 0.0;
	dda->delta->x = BIG_DOUBLE;
	dda->delta->y = BIG_DOUBLE;
	if (ray_dir->x != 0)
		dda->delta->x = fabs(1 / ray_dir->x);
	if (ray_dir->y != 0)
		dda->delta->y = fabs(1 / ray_dir->y);
	is_vertical_side = false;
	//
	if (ray_dir->x < 0)
	{
		dda->step->x = -1.0;
		dda->side->x = (ctx->player.pos->x - dda->cell->x) * dda->delta->x;
	}
	else
	{
		dda->step->x = 1.0;
		dda->side->x = (dda->cell->x + 1.0 - ctx->player.pos->x)
			* dda->delta->x;
	}
	if (ray_dir->y < 0)
	{
		dda->step->y = -1.0;
		dda->side->y = (ctx->player.pos->y - dda->cell->y) * dda->delta->y;
	}
	else
	{
		dda->step->y = 1.0;
		dda->side->y = (dda->cell->y + 1.0 - ctx->player.pos->y)
			* dda->delta->y;
	}
	// cool separator
	// have max_iteration for safety
	while (42)
	{
		if (dda->side->x < dda->side->y)
		{
			dda->side->x += dda->delta->x;
			dda->cell->x += dda->step->x;
			is_vertical_side = false;
		}
		else
		{
			dda->side->y += dda->delta->y;
			dda->cell->y += dda->step->y;
			is_vertical_side = true;
		}
		// TODO: care about _END_TILE
		if (dda->cell->y < ctx->map.height
			&& dda->cell->x < tiles_len(ctx->map.tiles[(int)dda->cell->y])
			&& ctx->map.tiles[(int)dda->cell->y][(int)dda->cell->x] == WALL)
			break ;
	}
	if (!is_vertical_side)
		perp_wall_dist = (dda->side->x - dda->delta->x);
	else
		perp_wall_dist = (dda->side->y - dda->delta->y);
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
