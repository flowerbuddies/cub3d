/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etattevi <etattevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 21:33:13 by etattevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ctx	*get_ctx(void)
{
	static t_ctx	ctx;

	return (&ctx);
}

static void	init_mlx(t_ctx *ctx)
{
	ctx->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!ctx->mlx)
		error(NULL, NULL);
	mlx_set_cursor_mode(ctx->mlx, MLX_MOUSE_HIDDEN);
}

static void	draw_fps_counter(t_ctx *ctx)
{
	static char			*fps;
	static mlx_image_t	*fps_counter;

	fps = ft_itoa(1.0 / ctx->mlx->delta_time);
	if (fps_counter)
		mlx_delete_image(ctx->mlx, fps_counter);
	fps_counter = mlx_put_string(ctx->mlx, fps, WIDTH - 35, 0);
	fps_counter->instances[0].z = 1;
	free(fps);
}

int	main(int ac, char **av)
{
	t_ctx	*ctx;

	if (ac != 2)
		error(NULL, "Invalid number of arguments");
	ctx = get_ctx();
	ft_bzero(ctx, sizeof(t_ctx));
	parse(av[1], ctx);
	init_mlx(ctx);
	init_background(ctx);
	init_minimap(ctx);
	init_raycast(ctx);
	draw_minimap(ctx);
	draw_raycast(ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)cursor_hook, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)keys_hook, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)draw_fps_counter, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)animate_sky, ctx);
	mlx_loop(ctx->mlx);
	free_ctx();
}
