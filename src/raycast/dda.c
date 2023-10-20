/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:54 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/20 17:22:41 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_check_dir(t_vec2 *ray_dir, const t_dda *dda, const t_vec2 *pos)
{
	if (ray_dir->x < 0)
	{
		dda->step_dir->x = -1;
		dda->side_dist->x = (pos->x - dda->cell->x) * dda->delta_dist->x;
	}
	else
	{
		dda->step_dir->x = 1;
		dda->side_dist->x = (dda->cell->x + 1.0 - pos->x) * dda->delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		dda->step_dir->y = -1;
		dda->side_dist->y = (pos->y - dda->cell->y) * dda->delta_dist->y;
	}
	else
	{
		dda->step_dir->y = 1;
		dda->side_dist->y = (dda->cell->y + 1.0 - pos->y) * dda->delta_dist->y;
	}
}

static void	init_dda(t_ctx *ctx)
{
	const t_dda	*dda = &(ctx->player.dda);

	dda->cell->x = ctx->player.pos->x;
	dda->cell->y = ctx->player.pos->y;
	dda->delta_dist->x = BIG_DOUBLE;
	dda->delta_dist->y = BIG_DOUBLE;
	if (ctx->player.ray_dir->x != 0)
		dda->delta_dist->x = fabs(1.0 / ctx->player.ray_dir->x);
	if (ctx->player.ray_dir->y != 0)
		dda->delta_dist->y = fabs(1.0 / ctx->player.ray_dir->y);
}

static bool	has_hit_wall(t_ctx *ctx, const t_dda *dda)
{
	// TODO: care about _END_TILE
	return (dda->cell->y < ctx->map.height
		&& dda->cell->x < get_tiles_len(ctx->map.tiles[dda->cell->y])
		&& ctx->map.tiles[dda->cell->y][dda->cell->x] == WALL);
}

double	dda(t_ctx *ctx)
{
	const t_dda	*dda = &(ctx->player.dda);
	bool		is_vertical_side;

	init_dda(ctx);
	dda_check_dir(ctx->player.ray_dir, &ctx->player.dda, ctx->player.pos);
	while (!has_hit_wall(ctx, dda))
	{
		if (dda->side_dist->x < dda->side_dist->y)
		{
			dda->side_dist->x += dda->delta_dist->x;
			dda->cell->x += dda->step_dir->x;
			is_vertical_side = false;
		}
		else
		{
			dda->side_dist->y += dda->delta_dist->y;
			dda->cell->y += dda->step_dir->y;
			is_vertical_side = true;
		}
	}
	if (!is_vertical_side)
		return (dda->side_dist->x - dda->delta_dist->x);
	return (dda->side_dist->y - dda->delta_dist->y);
}
