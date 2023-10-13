/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:27:38 by hunam             #+#    #+#             */
/*   Updated: 2023/10/13 17:28:13 by marmulle         ###   ########.fr       */
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
	if (assets->north)
		mlx_delete_texture(assets->north);
	if (assets->south)
		mlx_delete_texture(assets->south);
	if (assets->east)
		mlx_delete_texture(assets->east);
	if (assets->west)
		mlx_delete_texture(assets->west);
	if (assets->ceiling)
		free(assets->ceiling);
	if (assets->floor)
		free(assets->floor);
}

void	free_tilemap(t_map *map)
{
	int	y;

	y = -1;
	if (!map->tilemap)
		return ;
	while (++y < map->height && map->tilemap[y])
		free(map->tilemap[y]);
	free(map->tilemap);
}
