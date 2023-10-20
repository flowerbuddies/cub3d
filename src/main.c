/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/20 18:21:29 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	debug_tilemap(t_map *map)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width && map->tiles[y][x] != _END_TILE; x++)
		{
			if (map->tiles[y][x] == FLOOR)
				write(1, "0", 1);
			else if (map->tiles[y][x] == WALL)
				write(1, "1", 1);
			else if (map->tiles[y][x] == VOID)
				write(1, ".", 1);
		}
		write(1, "\n", 1);
	}
}

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
	ft_bzero(ctx, sizeof(*ctx));
	parse(av[1], ctx);
	debug_tilemap(&ctx->map); // TODO: rm
	init_mlx(ctx);
	init_minimap(ctx);
	draw_minimap(ctx); // TODO: move
	//
	init_raycast(ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)keys_hook, ctx);
	mlx_loop_hook(ctx->mlx, (t_hook)raycast, ctx);
	mlx_loop(ctx->mlx);
	free_ctx();
}
