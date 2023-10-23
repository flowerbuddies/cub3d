/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:21:53 by hunam             #+#    #+#             */
/*   Updated: 2023/10/23 18:20:28 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_point(t_minimap *mini, int x, int y, int color)
{
	int	j;
	int	i;

	j = -1;
	while (++j < mini->scale)
	{
		i = -1;
		while (++i < mini->scale)
			mlx_put_pixel(mini->img, x * mini->scale + i, y * mini->scale + j,
				color);
	}
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	draw_player(t_ctx *ctx)
{
	const int	size = ctx->mini.scale >> 2;
	int			x;
	int			y;

	y = -size;
	while (++y < size)
	{
		x = -size;
		while (++x < size)
			mlx_put_pixel(ctx->mini.img, ctx->player.pos->x * ctx->mini.scale
				+ x, ctx->player.pos->y * ctx->mini.scale + y,
				MINIMAP_VOID_COLOR * 2);
	}
}

void	init_minimap(t_ctx *ctx)
{
	ctx->mini.scale = min(WIDTH * MINIMAP_SIZE / ctx->map.width, HEIGHT
			* MINIMAP_SIZE / ctx->map.height);
	ctx->mini.img = mlx_new_image(ctx->mlx, ctx->mini.scale * ctx->map.width,
			ctx->mini.scale * ctx->map.height);
	if (!ctx->mini.img)
		error(ctx->mlx, NULL);
	if (mlx_image_to_window(ctx->mlx, ctx->mini.img, 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->mini.img->instances[0].z = 2;
}

void	draw_minimap(t_ctx *ctx)
{
	int		y;
	int		x;
	bool	trailing;

	y = -1;
	while (++y < ctx->map.height)
	{
		x = -1;
		trailing = false;
		while (++x < ctx->map.width)
		{
			if (trailing || ctx->map.tiles[y][x] == VOID)
				draw_point(&ctx->mini, x, y, MINIMAP_VOID_COLOR);
			else if (ctx->map.tiles[y][x] == _END_TILE)
			{
				--x;
				trailing = true;
			}
			else if (ctx->map.tiles[y][x] == WALL)
				draw_point(&ctx->mini, x, y, MINIMAP_WALL_COLOR);
			else
				draw_point(&ctx->mini, x, y, MINIMAP_FLOOR_COLOR);
		}
	}
	draw_player(ctx);
}
