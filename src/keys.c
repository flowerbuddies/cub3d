/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:06:36 by hunam             #+#    #+#             */
/*   Updated: 2023/10/20 18:29:23 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_camera(mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(img, x, y, 0);
	}
}

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
	clear_camera(player->camera);
}

void	keys_hook(t_ctx *ctx)
{
	const double	rot_speed = ctx->mlx->delta_time * 3;

	if (mlx_is_key_down(ctx->mlx, MLX_KEY_LEFT))
		rot_cam(&ctx->player, -rot_speed);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_RIGHT))
		rot_cam(&ctx->player, rot_speed);
}
