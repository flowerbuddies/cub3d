/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:42:32 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/17 19:37:13 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_avatar(t_ctx *ctx)
{
	const int		color = 0xFFFF00FF;
	const int		scale = ctx->mini.scale >> 2;
	const t_vec2	pos = {ctx->player.pos->x * ctx->mini.scale, ctx->player.pos->y * ctx->mini.scale};
	int				x;
	int				y;

	y = -scale;
	while (++y < scale)
	{
		x = -scale;
		while (++x < scale)
		{
			mlx_put_pixel(ctx->mini.img, pos.x + x, pos.y + y, color);
		}
	}

}

// static void	draw_vision(t_ctx *ctx)
// {
// 	;
// }

void	draw_player(t_ctx *ctx)
{
	// draw_vision(ctx);
	draw_avatar(ctx);
}
