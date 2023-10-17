/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:42:19 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/17 15:14:21 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tiles_len(t_tile *tiles)
{
	int	i;

	i = 0;
	while (*tiles++)
		i++;
	return (i);
}

static bool	is_surrounded_by_walls(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height)
		return (false);
	if (x > tiles_len(map->tiles[y - 1]) || x > tiles_len(map->tiles[y + 1]))
		return (false);
	if (map->tiles[y - 1][x] == VOID || map->tiles[y + 1][x] == VOID)
		return (false);
	if (x == 0 || map->tiles[y][x + 1] == _END_TILE)
		return (false);
	if (map->tiles[y][x - 1] == VOID || map->tiles[y][x + 1] == VOID)
		return (false);
	return (true);
}

void	check_map_validity(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->tiles[y][++x] != _END_TILE)
			if (map->tiles[y][x] == FLOOR && !is_surrounded_by_walls(map, x, y))
				(free_ctx(), error(NULL, "Map not closed"));
	}
}
