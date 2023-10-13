/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:42:19 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 20:41:26 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// parse map, every  space set to X
// from every 0 do 1 step of floodfill
// if any reach X, invalid map

// instead of get_row_len:
// a) tiles is array of t_row
// struct s_row {
// 	t_tile	*tiles;
// 	int		len;
// }
//
// b) map also has array of row lengths
static int	get_row_len(t_map *map, int y)
{
	int	len;

	len = 0;
	while (map->tiles[y][len] != _END_TILE)
		len++;
	return (len);
}

static void	check_vertical(t_map *map, int x, int y)
{
	int	next_len;

	if (y == 0)
		(free_the()->map(), error(NULL, "Unclosed map on upper edge"));
	if (y == map->height)
		(free_the()->map(), error(NULL, "Unclosed map on lower edge"));
	next_len = get_row_len(map, y - 1);
	if (x >= next_len)
		(free_the()->map(), error(NULL, "Unclosed map due to short upper row"));
	next_len = get_row_len(map, y + 1);
	if (x >= next_len)
		(free_the()->map(), error(NULL, "Unclosed map due to short lower row"));
	if (map->tiles[y - 1][x] == VOID || map->tiles[y + 1][x] == VOID)
		(free_the()->map(), error(NULL, "Out of bounds inside map"));
}

static void	check_horizontal(t_map *map, int x, int y)
{
	int	row_len;

	if (x == 0)
		(free_the()->map(), error(NULL, "Unclosed map on left edge"));
	row_len = get_row_len(map, y);
	if (x + 1 == row_len)
		(free_the()->map(), error(NULL, "Unclosed map on right edge"));
	if (map->tiles[y][x - 1] == VOID || map->tiles[y][x + 1] == VOID)
		(free_the()->map(), error(NULL, "Out of bounds inside map"));
}

void	check_map_validity(t_map *map)
{
	t_tile	tile;
	bool	found_player;
	int		y;
	int		x;

	found_player = false;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width && map->tiles[y][x] != _END_TILE)
		{
			tile = map->tiles[y][x];
			if (tile == FLOOR || tile == PLAYER)
			{
				if (tile == PLAYER && found_player)
					(free_the()->map(), error(NULL, "Too many spawn points"));
				else if (tile == PLAYER && !found_player)
					found_player = true;
				check_vertical(map, x, y);
				check_horizontal(map, x, y);
			}
		}
	}
}
