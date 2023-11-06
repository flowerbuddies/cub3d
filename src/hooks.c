/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:06:36 by hunam             #+#    #+#             */
/*   Updated: 2023/11/06 14:45:00 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_collision(t_ctx *ctx, t_vec2f *new_pos)
{
	return (get_tile(&ctx->map, new_pos->x, new_pos->y) != FLOOR);
}

static void	move_player(t_ctx *ctx, char dir)
{
	const double	move_speed = ctx->mlx->delta_time
		* 3 * ((dir == 'w' || dir == 'd') * 2 - 1);
	t_vec2f			new_pos;

	if (dir == 'w' || dir == 's')
	{
		new_pos.x = ctx->player.pos->x + ctx->player.dir->x * move_speed;
		new_pos.y = ctx->player.pos->y + ctx->player.dir->y * move_speed;
		if (!is_collision(ctx, &new_pos))
		{
			ctx->player.pos->y += ctx->player.dir->y * move_speed;
			ctx->player.pos->x += ctx->player.dir->x * move_speed;
		}
	}
	else if (dir == 'a' || dir == 'd')
	{
		new_pos.x = ctx->player.pos->x + -ctx->player.dir->y * move_speed;
		new_pos.y = ctx->player.pos->y + ctx->player.dir->x * move_speed;
		if (!is_collision(ctx, &new_pos))
		{
			ctx->player.pos->y += ctx->player.dir->x * move_speed;
			ctx->player.pos->x += -ctx->player.dir->y * move_speed;
		}
	}
	clear_img(ctx->player.camera);
}

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
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_W)) //TODO: benchmark vs mlx_key_hook
		move_player(ctx, 'w');
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_S))
		move_player(ctx, 's');
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_A))
		move_player(ctx, 'a');
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_D))
		move_player(ctx, 'd');
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		(free_ctx(), exit(0));
	draw_minimap(ctx);
	draw_raycast(ctx);
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
