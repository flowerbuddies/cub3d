/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:21:53 by hunam             #+#    #+#             */
/*   Updated: 2023/10/17 19:51:51 by hunam            ###   ########.fr       */
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
	const double	width = WIDTH * .25;
	const double	height = HEIGHT * .25;

	ctx->mini.scale = min(width / ctx->map.width, height / ctx->map.height);
	// if (ctx->mini.img)
	// 	mlx_delete_image(ctx->mlx, ctx->mini.img);
	ctx->mini.img = mlx_new_image(ctx->mlx, width, height);
	if (!ctx->mini.img)
		error(ctx->mlx, NULL);
	mlx_image_to_window(ctx->mlx, ctx->mini.img, 0, 0);
}

void	resize_minimap(t_ctx *ctx, double factor)
{
	if (factor < 1)
	{
		if (ctx->mini.increased_count <= 0)
			return ;
		--ctx->mini.increased_count;
	}
	else
		++ctx->mini.increased_count;
	// int offset = ctx->mini.img->width * factor
	mlx_resize_image(ctx->mini.img, ctx->mini.img->width + factor,
		ctx->mini.img->height + factor);
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
}
