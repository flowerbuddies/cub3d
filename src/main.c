/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/21 20:11:15 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO maybe replace this by having a ref to ctx in all ctx fields,
// ie: make `player->ctx` possible
t_ctx	*get_ctx(void)
{
	static t_ctx	ctx;

	return (&ctx);
}

static void	init_mlx(t_ctx *ctx)
{
	// TODO: try to use mlx_get_monitor_size
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!ctx->mlx)
		error(NULL, NULL);
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
	init_minimap(ctx);
	init_raycast(ctx);
	mlx_cursor_hook(ctx->mlx, (mlx_cursorfunc)cursor_hook, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)keys_hook, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)draw_minimap, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)raycast, ctx);
	mlx_loop(ctx->mlx);
	free_ctx();
}
