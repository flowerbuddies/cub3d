/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:40:14 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/20 17:57:57 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_ctx *ctx)
{
	ctx->player.plane = vec2(0, FOV);
	ctx->player.ray_dir = vec2(0, 0);
	ctx->player.dda.cell = vec2_int(0, 0);
	ctx->player.dda.side_dist = vec2(0, 0);
	ctx->player.dda.delta_dist = vec2(0, 0);
	ctx->player.dda.step_dir = vec2_int(0, 0);
	ctx->player.camera = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->player.camera)
		error(ctx->mlx, NULL);
	if (mlx_image_to_window(ctx->mlx, ctx->player.camera, 0, 0) == -1)
		error(ctx->mlx, NULL);
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

static void	draw_vert_strips(t_ctx *ctx, int x, double ray_len)
{
	const int	line_height = (HEIGHT / ray_len);
	int			draw_start;
	int			draw_end;

	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
		mlx_put_pixel(ctx->player.camera, x, draw_start++, MINIMAP_WALL_COLOR
			* 2);
}

void	raycast(t_ctx *ctx)
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
		draw_hit(ctx, ray_len);
		draw_ray(ctx, ray_len);
		draw_vert_strips(ctx, ray, ray_len);
	}
}
