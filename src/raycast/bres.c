/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:57:33 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/19 18:34:06 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bres	init_bres(const t_vec2 *from, const t_vec2 *to)
{
	t_bres	b;

	b.dx = abs((int)to->x - (int)from->x);
	b.sx = -1;
	if (from->x < to->x)
		b.sx = 1;
	b.dy = -1 * abs((int)to->y - (int)from->y);
	b.sy = -1;
	if (from->y < to->y)
		b.sy = 1;
	b.err = b.dx + b.dy;
	b.x = (int)from->x;
	b.y = (int)from->y;
	return (b);
}

static void	draw_line(t_ctx *ctx, const t_vec2 *from, const t_vec2 *to)
{
	t_bres	b;

	b = init_bres(from, to);
	while (42)
	{
		mlx_put_pixel(ctx->mini.img, b.x, b.y, 0xFF000066);
		if (b.x == (int)to->x && b.y == (int)to->y)
			break ;
		b.e2 = 2 * b.err;
		if (b.e2 >= b.dy)
		{
			b.err += b.dy;
			b.x += b.sx;
		}
		if (b.e2 <= b.dx)
		{
			b.err += b.dx;
			b.y += b.sy;
		}
	}
}

void	draw_ray(t_ctx *ctx, t_vec2 *ray_dir, double ray_len)
{
	const t_vec2	*hit_pos = get_hit_pos(ctx->player.pos, ray_dir, ray_len);
	const t_vec2	*from = vec2(ctx->player.pos->x * ctx->mini.scale,
				ctx->player.pos->y * ctx->mini.scale);
	const t_vec2	*to = vec2(hit_pos->x * ctx->mini.scale, hit_pos->y
				* ctx->mini.scale);

	draw_line(ctx, from, to);
	free((void *)from);
	free((void *)to);
}
