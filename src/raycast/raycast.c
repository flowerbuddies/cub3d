/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/19 18:21:41 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_ctx *ctx)
{
	ctx->player.plane = vec2(0.0, 0.7);
	ctx->player.dda.side = vec2(0.0, 0.0);
	ctx->player.dda.delta = vec2(0.0, 0.0);
	ctx->player.dda.step = vec2_int(0, 0);
	ctx->player.dda.cell = vec2_int(0, 0);
}

t_vec2	*get_hit_pos(t_vec2 *pos, t_vec2 *ray_dir, double ray_len)
{
	return (vec2(pos->x + ray_dir->x * ray_len, pos->y + ray_dir->y * ray_len));
}

void	draw_hit(t_ctx *ctx, t_vec2 *ray_dir, double ray_len)
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
		draw_ray(ctx, ray_dir, ray_len);
	}
	free(ray_dir);
}
