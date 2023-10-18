/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:21:53 by hunam             #+#    #+#             */
/*   Updated: 2023/10/18 18:12:20 by marmulle         ###   ########.fr       */
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

void	init_minimap(t_ctx *ctx)
{
	const int	width = WIDTH * .75;
	const int	height = HEIGHT * .75;

	ctx->mini.scale = min(width / ctx->map.width, height / ctx->map.height);
	ctx->mini.img = mlx_new_image(ctx->mlx, width, height);
	if (!ctx->mini.img)
		error(ctx->mlx, NULL);
	mlx_image_to_window(ctx->mlx, ctx->mini.img, 0, 0);
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
