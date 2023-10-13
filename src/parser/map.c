/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:42:32 by hunam             #+#    #+#             */
/*   Updated: 2023/10/13 20:39:23 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_nl(int fd)
{
	char	*line;

	while (42)
	{
		line = gnl_no_nl(fd);
		if (!line)
			(free_the()->map(), error(NULL, "No map found"));
		if (line[0])
			return (line);
		free(line);
	}
}

static void	first_tiles_row(t_map *map, t_tile *tiles)
{
	map->tiles = malloc(sizeof(t_tile *));
	if (!map->tiles)
		error(NULL, NULL);
	map->tiles[0] = tiles;
	map->height = 1;
}

static void	append_tiles(t_map *map, t_tile *tiles)
{
	t_tile	**new_tilemap;
	int		i;

	if (!map->tiles)
		return (first_tiles_row(map, tiles));
	map->height++;
	new_tilemap = malloc(sizeof(t_tile *) * map->height);
	if (!new_tilemap)
		error(NULL, NULL);
	i = -1;
	while (++i < map->height - 1)
		new_tilemap[i] = map->tiles[i];
	new_tilemap[i] = tiles;
	free(map->tiles);
	map->tiles = new_tilemap;
}

static t_tile	*get_tiles(t_map *map, char *line)
{
	t_tile		*tiles;
	int			i;
	const int	len = ft_strlen(line);

	tiles = malloc(sizeof(t_tile) * (len + 1));
	if (!tiles)
		error(NULL, NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			tiles[i] = VOID;
		else if (line[i] == '0')
			tiles[i] = FLOOR;
		else if (line[i] == '1')
			tiles[i] = WALL;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			tiles[i] = PLAYER;
		else
			(free(line), free(tiles), free_the()->map(), error(NULL,
					"Bad character in the map"));
	}
	tiles[i] = _END_TILE;
	if (len > map->width)
		map->width = len;
	return (tiles);
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	bool	seen_empty_line;

	line = skip_nl(fd);
	seen_empty_line = false;
	while (line)
	{
		if (!line[0])
			seen_empty_line = true;
		else if (seen_empty_line)
			(free(line), free_the()->map(), error(NULL,
					"Empty line inside the map"));
		else
			append_tiles(map, get_tiles(map, line));
		free(line);
		line = gnl_no_nl(fd);
	}
}
