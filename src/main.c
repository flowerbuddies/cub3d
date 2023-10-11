/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:30 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/12 01:58:04 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		error(NULL, "Invalid number of arguments");
	parse(av[1], &ctx);
	// TODO: may not be necessary when we get the graphics part as when linked to ctx.mlx they might be freed automatically
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
