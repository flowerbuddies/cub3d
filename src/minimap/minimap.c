/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:21:53 by hunam             #+#    #+#             */
/*   Updated: 2023/10/16 19:15:33 by hunam            ###   ########.fr       */
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

void	init_minimap(t_ctx *ctx)
{
	ctx->mini.scale = 10;
	ctx->mini.img = mlx_new_image(ctx->mlx, ctx->map.width * ctx->mini.scale,
			ctx->map.height * ctx->mini.scale);
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
			if (trailing)
				draw_point(&ctx->mini, x, y, 0xeef2f3FF);
			else if (ctx->map.tiles[y][x] == _END_TILE)
			{
				draw_point(&ctx->mini, x, y, 0xeef2f3FF);
				trailing = true;
			}
			else if (ctx->map.tiles[y][x] == WALL)
				draw_point(&ctx->mini, x, y, 0x9785bdFF);
			else
				draw_point(&ctx->mini, x, y, 0xeef2f3FF);
		}
	}
}
