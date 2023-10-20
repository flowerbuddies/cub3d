/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:06:36 by hunam             #+#    #+#             */
/*   Updated: 2023/10/20 20:26:21 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rot_cam(t_player *player, double speed)
{
	const double	old_dir_x = player->dir->x;
	const double	old_plane_x = player->plane->x;
	const double	cos_speed = cos(speed);
	const double	sin_speed = sin(speed);

	player->dir->x = old_dir_x * cos_speed - player->dir->y * sin_speed;
	player->dir->y = old_dir_x * sin_speed + player->dir->y * cos_speed;
	player->plane->x = old_plane_x * cos_speed - player->plane->y * sin_speed;
	player->plane->y = old_plane_x * sin_speed + player->plane->y * cos_speed;
	clear_img(player->camera);
}

void	keys_hook(t_ctx *ctx)
{
	const double	rot_speed = ctx->mlx->delta_time * 3;

	if (mlx_is_key_down(ctx->mlx, MLX_KEY_LEFT))
		rot_cam(&ctx->player, -rot_speed);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_RIGHT))
		rot_cam(&ctx->player, rot_speed);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		(free_ctx(), exit(0));
}

void	cursor_hook(double x, double y, t_ctx *ctx)
{
	static double	old_x = WIDTH / 2;

	(void)y;
	rot_cam(&ctx->player, (x - old_x) / 200);
	old_x = x;
}
