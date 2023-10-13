/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:27:38 by hunam             #+#    #+#             */
/*   Updated: 2023/10/12 18:42:31 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		free((char *)obj[i++]);
	free(obj);
}

void	free_assets(t_assets *assets)
{
	mlx_delete_texture(assets->north);
	mlx_delete_texture(assets->south);
	mlx_delete_texture(assets->east);
	mlx_delete_texture(assets->west);
	free(assets->ceiling);
	free(assets->floor);
}

void	free_map(t_map *map)
{
	(void) map;
	// free_2d((const char **)map->tilemap);
}
