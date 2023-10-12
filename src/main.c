/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/12 18:43:54 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	debug_tilemap(t_map *map)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width && map->tilemap[y][x] != _END_TILES; x++)
		{
			if (map->tilemap[y][x] == FLOOR)
				write(1, "0", 1);
			else if (map->tilemap[y][x] == WALL)
				write(1, "1", 1);
			else if (map->tilemap[y][x] == SPACE)
				write(1, "#", 1);
			else if (map->tilemap[y][x] == NORTH)
				write(1, "N", 1);
			else if (map->tilemap[y][x] == SOUTH)
				write(1, "S", 1);
			else if (map->tilemap[y][x] == EAST)
				write(1, "E", 1);
			else if (map->tilemap[y][x] == WEST)
				write(1, "W", 1);
		}
		write(1, "\n", 1);
	}
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		error(NULL, "Invalid number of arguments");
	parse(av[1], &ctx);
	// TODO: may not be necessary when we get the graphics part as when linked to ctx.mlx they might be freed automatically
	debug_tilemap(&ctx.map);
	free_assets(&ctx.assets);
	free_map(&ctx.map);

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
