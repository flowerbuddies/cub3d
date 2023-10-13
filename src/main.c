/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 22:18:31 by hunam            ###   ########.fr       */
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
				write(1, "#", 1);
		}
		write(1, "\n", 1);
	}
}

t_ctx	*get_ctx(void)
{
	static t_ctx	ctx;

	return (&ctx);
}

int	main(int ac, char **av)
{
	t_ctx	*ctx;

	if (ac != 2)
		error(NULL, "Invalid number of arguments");
	ctx = get_ctx();
	ft_bzero(ctx, sizeof(*ctx));
	parse(av[1], ctx);
	debug_tilemap(&ctx->map);
	free_ctx();
	// map.mlx = mlx_init(WIDTH, HEIGHT, "cub3d!", true);
	// if (!map.mlx)
	// 	return (error(NULL, NULL));
	// map.mini.image = mlx_new_image(map.mlx, map.mini.width, map.mini.height);
	// if (!map.mini.image)
	// 	return (error(map.mlx, NULL));
	// if (mlx_image_to_window(map.mlx, map.mini.image, 0, 0) == -1)
	// 	return (error(map.mlx, NULL));
	// // mlx_loop_hook(mlx, ft_randomize, mlx);
	// // mlx_loop_hook(mlx, ft_hook, mlx);
	// // mlx_loop(map.mlx);
	// mlx_terminate(map.mlx);
}
