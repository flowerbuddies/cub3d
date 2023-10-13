/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:42:19 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 13:48:50 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// parse map, every  space set to X
// from every 0 do 1 step of floodfill
// if any reach X, invalid map


// instead of get_row_len:
// a) tilemap is array of t_row
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
	while (map->tilemap[y][len] != _END_TILE)
		len++;
	return (len);
}

static void	check_up(t_map *map, int x, int y)
{
	int	upper_len;

	if (y == 0)
		error(NULL, "Unclosed map on upper edge");
	upper_len = get_row_len(map, y - 1);
	if (x >= upper_len)
		error(NULL, "Unclosed map due to short upper row");
	if (map->tilemap[y - 1][x] == BOUNDS)
		error(NULL, "Out of bounds inside map");
}

static void	check_down(t_map *map, int x, int y)
{
	int	lower_len;

	if (y == map->height)
		error(NULL, "Unclosed map on lower edge");
	lower_len = get_row_len(map, y + 1);
	if (x >= lower_len)
		error(NULL, "Unclosed map due to short lower row");
	if (map->tilemap[y + 1][x] == BOUNDS)
		error(NULL, "Out of bounds inside map");
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
		while (++x < map->width && map->tilemap[y][x] != _END_TILE)
		{
			tile = map->tilemap[y][x];
			if (tile == FLOOR || tile == PLAYER)
			{
				if (tile == PLAYER && found_player)
					error(NULL, "Too many spawn points"); // TODO: free map
				else if (tile == PLAYER && !found_player)
					found_player = true;
				check_up(map, x, y);
				check_down(map, x, y);
			}
		}
	}
}
