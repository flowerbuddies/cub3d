/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:06:36 by hunam             #+#    #+#             */
/*   Updated: 2023/10/21 20:24:20 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rot_cam(t_ctx *ctx, double speed)
{
	const t_player	*player = &ctx->player;
	const double	old_dir_x = player->dir->x;
	const double	old_plane_x = player->plane->x;
	const double	cos_speed = cos(speed);
	const double	sin_speed = sin(speed);

	player->dir->x = old_dir_x * cos_speed - player->dir->y * sin_speed;
	player->dir->y = old_dir_x * sin_speed + player->dir->y * cos_speed;
	player->plane->x = old_plane_x * cos_speed - player->plane->y * sin_speed;
	player->plane->y = old_plane_x * sin_speed + player->plane->y * cos_speed;
	clear_img(player->camera);
	clear_img(ctx->mini.img);
}

void	keys_hook(t_ctx *ctx)
{
	const double	rot_speed = ctx->mlx->delta_time * 3;

	if (mlx_is_key_down(ctx->mlx, MLX_KEY_LEFT))
		rot_cam(ctx, -rot_speed);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_RIGHT))
		rot_cam(ctx, rot_speed);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		(free_ctx(), exit(0));
}

void	cursor_hook(double x, double y, t_ctx *ctx)
{
	static double	old_x = INT_MAX;

	(void)y;
	if (old_x == INT_MAX)
		old_x = x;
	rot_cam(ctx, (x - old_x) / 200);
	old_x = x;
}
