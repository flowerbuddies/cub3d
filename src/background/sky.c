/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:40:48 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/08 14:09:11 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_animated_sky(t_ctx *ctx)
{
	mlx_texture_t	*sprites[3];

	sprites[0] = mlx_load_png("assets/textures/sky/frame0.png");
	sprites[1] = mlx_load_png("assets/textures/sky/frame1.png");
	sprites[2] = mlx_load_png("assets/textures/sky/frame2.png");
	if (!sprites[0] || !sprites[1] || !sprites[2])
		error(ctx->mlx, NULL);
	ctx->assets.animated_sky[0] = mlx_texture_to_image(ctx->mlx, sprites[0]);
	ctx->assets.animated_sky[1] = mlx_texture_to_image(ctx->mlx, sprites[1]);
	ctx->assets.animated_sky[2] = mlx_texture_to_image(ctx->mlx, sprites[2]);
	if (!ctx->assets.animated_sky[0] || !ctx->assets.animated_sky[1]
		|| !ctx->assets.animated_sky[2])
		error(ctx->mlx, NULL);
	(mlx_delete_texture(sprites[0]), mlx_delete_texture(sprites[1]),
		mlx_delete_texture(sprites[2]));
	if (mlx_image_to_window(ctx->mlx, ctx->assets.animated_sky[0], 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->assets.animated_sky[0]->instances[0].z = -2;
	if (mlx_image_to_window(ctx->mlx, ctx->assets.animated_sky[1], 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->assets.animated_sky[1]->instances[0].z = -3;
	if (mlx_image_to_window(ctx->mlx, ctx->assets.animated_sky[2], 0, 0) == -1)
		error(ctx->mlx, NULL);
	ctx->assets.animated_sky[2]->instances[0].z = -4;
}

void	draw_static_sky(t_ctx *ctx)
{
	mlx_image_t	*sky;

	sky = mlx_new_image(ctx->mlx, WIDTH, HEIGHT / 2);
	draw_half(sky, *ctx->assets.sky);
	if (mlx_image_to_window(ctx->mlx, (mlx_image_t *)sky, 0, 0) == -1)
		error(ctx->mlx, NULL);
	sky->instances[0].z = -1;
}

void	animate_sky(t_ctx *ctx)
{
	static int	delta = 20;
	int			i;

	if (*ctx->assets.sky != SECRET)
		return ;
	delta--;
	if (delta != 0)
		return ;
	delta = 20;
	i = -1;
	while (++i < 3)
	{
		if (ctx->assets.animated_sky[i]->instances[0].z == -2)
			ctx->assets.animated_sky[i]->instances[0].z = -4;
		else
			ctx->assets.animated_sky[i]->instances[0].z++;
	}
}
