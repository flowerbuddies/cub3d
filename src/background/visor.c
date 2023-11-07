/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:16:24 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/07 14:07:02 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_texture_transparent(mlx_texture_t *texture, int transparency)
{
	const int	pixels_length = texture->height 
		* texture->width * texture->bytes_per_pixel;
	int			i;

	if (transparency > 255)
		transparency = 255;
	else if (transparency < 0)
		transparency = 0;
	i = texture->bytes_per_pixel - 1;
	while (i < pixels_length)
	{
		texture->pixels[i] = transparency;
		i += texture->bytes_per_pixel;
	}
}

mlx_image_t	*scale_texture_to_window(mlx_texture_t *texture)
{
	return 
}

static void	init_visor(t_ctx *ctx)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("assets/textures/visor.png");
	if (!texture)
		error(ctx->mlx, NULL);
	make_texture_transparent(texture, VISOR_TRANSPARENCY);
	ctx->assets.visor = mlx_texture_to_image(ctx->mlx, texture);
	if (!ctx->assets.visor)
		error(ctx->mlx, NULL);
	// ctx->assets.visor->instances[0].z = 10;
}


void	draw_visor(t_ctx *ctx)
{
	init_visor(ctx);
	mlx_image_to_window(ctx->mlx, ctx->assets.visor, 0, 0);
}
