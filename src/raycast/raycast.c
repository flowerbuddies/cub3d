/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/20 17:22:01 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_player *player)
{
	player->plane = vec2(0, FOV);
	player->ray_dir = vec2(0, 0);
	player->dda.cell = vec2_int(0, 0);
	player->dda.side_dist = vec2(0, 0);
	player->dda.delta_dist = vec2(0, 0);
	player->dda.step_dir = vec2_int(0, 0);
}

t_vec2	*get_hit_pos(t_vec2 *pos, t_vec2 *ray_dir, double ray_len)
{
	return (vec2(pos->x + ray_dir->x * ray_len, pos->y + ray_dir->y * ray_len));
}

static void	draw_hit(t_ctx *ctx, double ray_len)
{
	const t_vec2	*hit_pos = get_hit_pos(ctx->player.pos, ctx->player.ray_dir,
				ray_len);
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
	free((void *)hit_pos);
}

void	raycast(t_ctx *ctx)
{
	double	ray;
	double	camera_x;
	double	ray_len;

	ray = -1;
	while (++ray < MAX_RAYS)
	{
		camera_x = 2.0 * ray / MAX_RAYS - 1;
		ctx->player.ray_dir->x = ctx->player.dir->x + ctx->player.plane->x
			* camera_x;
		ctx->player.ray_dir->y = ctx->player.dir->y + ctx->player.plane->y
			* camera_x;
		ray_len = dda(ctx);
		draw_hit(ctx, ray_len);
		draw_ray(ctx, ray_len);
	}
}
