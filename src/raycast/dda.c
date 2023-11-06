/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:54 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 16:16:57 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2f	*vec2f(double x, double y)
{
	t_vec2f	*out;

	out = malloc(sizeof(t_vec2f));
	if (!out)
		error(NULL, NULL);
	out->x = x;
	out->y = y;
	return (out);
}

t_vec2i	*vec2i(int x, int y)
{
	t_vec2i	*out;

	out = malloc(sizeof(t_vec2i));
	if (!out)
		error(NULL, NULL);
	out->x = x;
	out->y = y;
	return (out);
}

static void	check_dir(t_vec2f *ray_dir, const t_dda *dda, const t_vec2f *pos)
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
	const t_dda	*dda = &(ctx->raycast.dda);

	dda->cell->x = ctx->player.pos->x;
	dda->cell->y = ctx->player.pos->y;
	dda->delta_dist->x = BIG_DOUBLE;
	dda->delta_dist->y = BIG_DOUBLE;
	if (ctx->raycast.ray_dir->x != 0)
		dda->delta_dist->x = fabs(1.0 / ctx->raycast.ray_dir->x);
	if (ctx->raycast.ray_dir->y != 0)
		dda->delta_dist->y = fabs(1.0 / ctx->raycast.ray_dir->y);
}

double	dda(t_ctx *ctx)
{
	const t_dda	*dda = &(ctx->raycast.dda);

	init_dda(ctx);
	check_dir(ctx->raycast.ray_dir, &ctx->raycast.dda, ctx->player.pos);
	while (get_tile(&ctx->map, dda->cell->x, dda->cell->y) == FLOOR)
	{
		if (dda->side_dist->x < dda->side_dist->y)
		{
			dda->side_dist->x += dda->delta_dist->x;
			dda->cell->x += dda->step_dir->x;
			*dda->is_vertical_side = false;
		}
		else
		{
			dda->side_dist->y += dda->delta_dist->y;
			dda->cell->y += dda->step_dir->y;
			*dda->is_vertical_side = true;
		}
	}
	if (!*dda->is_vertical_side)
		return (dda->side_dist->x - dda->delta_dist->x);
	return (dda->side_dist->y - dda->delta_dist->y);
}
