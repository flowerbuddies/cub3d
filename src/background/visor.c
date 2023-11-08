/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:16:24 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/08 14:03:02 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_texture_transparent(mlx_texture_t *texture, int transparency)
{
	const int	pixels_length = texture->height * texture->width
			* texture->bytes_per_pixel;
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

mlx_image_t	*scale_texture_to_window(t_ctx *ctx, mlx_texture_t *texture)
{
	mlx_image_t	*image;
	int			x;
	int			y;
	int			i;
	double		tex_x;
	double		tex_y;
	int			tex_i;

	image = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!image)
		error(ctx->mlx, NULL);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			tex_x = (double)x / WIDTH;
			tex_y = (double)y / HEIGHT;
			tex_i = tex_x * texture->width * texture->bytes_per_pixel + tex_y
				* texture->height * texture->bytes_per_pixel;
			i = x * sizeof(u_int8_t) + y * WIDTH * sizeof(u_int8_t);
			image->pixels[i] = texture->pixels[tex_i];
			image->pixels[i + 1] = texture->pixels[tex_i + 1];
			image->pixels[i + 2] = texture->pixels[tex_i + 2];
			image->pixels[i + 3] = texture->pixels[tex_i + 3];
		}
	}
	return (image);
}

static void	init_visor(t_ctx *ctx)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("assets/textures/visor.png");
	if (!texture)
		error(ctx->mlx, NULL);
	make_texture_transparent(texture, VISOR_TRANSPARENCY);
	ctx->assets.visor = mlx_texture_to_image(ctx->mlx, texture);
	// ctx->assets.visor = scale_texture_to_window(ctx, texture);
	if (!ctx->assets.visor)
		error(ctx->mlx, NULL);
	// ctx->assets.visor->instances[0].z = 10;
}

void	draw_visor(t_ctx *ctx)
{
	init_visor(ctx);
	mlx_image_to_window(ctx->mlx, ctx->assets.visor, 0, 0);
}
