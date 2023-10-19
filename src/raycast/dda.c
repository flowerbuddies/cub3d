/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:54 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/19 17:44:03 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_check_dir(t_vec2 *ray_dir, const t_dda *dda, const t_vec2 *pos)
{
	if (ray_dir->x != 0)
		dda->delta->x = fabs(1.0 / ray_dir->x);
	if (ray_dir->y != 0)
		dda->delta->y = fabs(1.0 / ray_dir->y);
	if (ray_dir->x < 0)
	{
		dda->step->x = -1.0;
		dda->side->x = (pos->x - dda->cell->x) * dda->delta->x;
	}
	else
	{
		dda->step->x = 1.0;
		dda->side->x = ((dda->cell->x + 1.0 - pos->x) * dda->delta->x);
	}
	if (ray_dir->y < 0)
	{
		dda->step->y = -1.0;
		dda->side->y = (pos->y - dda->cell->y) * dda->delta->y;
	}
	else
	{
		dda->step->y = 1.0;
		dda->side->y = (dda->cell->y + 1.0 - pos->y) * dda->delta->y;
	}
}

static void	init_dda(t_ctx *ctx, t_vec2 *ray_dir)
{
	const t_dda		*dda = &(ctx->player.dda);
	const t_vec2	*pos = ctx->player.pos;

	dda->cell->x = pos->x;
	dda->cell->y = pos->y;
	dda->side->x = 0.0;
	dda->side->y = 0.0;
	dda->delta->x = BIG_DOUBLE;
	dda->delta->y = BIG_DOUBLE;
	dda_check_dir(ray_dir, dda, pos);
}

static bool	has_hit_wall(t_ctx *ctx, const t_dda *dda)
{
	// TODO: care about _END_TILE
	return (dda->cell->y < ctx->map.height
		&& dda->cell->x < get_tiles_len(ctx->map.tiles[(int)dda->cell->y])
		&& ctx->map.tiles[(int)dda->cell->y][(int)dda->cell->x] == WALL);
}

double	dda(t_ctx *ctx, t_vec2 *ray_dir)
{
	const t_dda	*dda = &(ctx->player.dda);
	bool		is_vertical_side;

	is_vertical_side = false;
	init_dda(ctx, ray_dir);
	while (!has_hit_wall(ctx, dda))
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
	}
	if (!is_vertical_side)
		return (dda->side->x - dda->delta->x);
	return (dda->side->y - dda->delta->y);
}
