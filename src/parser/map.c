/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:42:32 by hunam             #+#    #+#             */
/*   Updated: 2023/10/12 18:35:12 by marmulle         ###   ########.fr       */
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
		{
			// TODO: handle leaks
			error(NULL, "No map found");
		}
		if (line[0])
			return (line);
		free(line);
	}
}

static void init_tilemap(t_map *map, t_tile *tiles)
{
	map->tilemap = malloc(sizeof(t_tile *));
	if (!map->tilemap)
		error(NULL, "Failed to allocate tilemap");
	map->tilemap[0] = tiles;
	map->height = 1;
}

static void	append_tiles(t_map *map, t_tile *tiles)
{
	t_tile	**new_tilemap;
	int		i;

	if (!map->tilemap)
		return (init_tilemap(map, tiles));
	map->height++;
	new_tilemap = malloc(sizeof(t_tile *) * map->height);
	if (!new_tilemap)
		error(NULL, "Failed to allocate tilemap");
	i = -1;
	while (++i < map->height - 1)
		new_tilemap[i] = map->tilemap[i];
	new_tilemap[i] = tiles;
	free(map->tilemap);
	map->tilemap = new_tilemap;
}

static t_tile	*get_tiles(t_map *map, char *line)
{
	t_tile		*tiles;
	int			i;
	const int	len = ft_strlen(line);

	tiles = malloc(sizeof(t_tile) * (len + 1));
	if (!tiles)
		error(NULL, "failed to allocate tiles");
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			tiles[i] = SPACE;
		else if (line[i] == '0')
			tiles[i] = FLOOR;
		else if (line[i] == '1')
			tiles[i] = WALL;
		else if (line[i] == 'N' || line[i] == 'S' 
			|| line[i] == 'E' || line[i] == 'W')
			tiles[i] = NORTH;
		else
			error(NULL, "Bad character in the map");
	}
	tiles[i] = _END_TILES;
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
			error(NULL, "Empty line inside the map");
		else
			append_tiles(map, get_tiles(map, line));
		free(line);
		line = gnl_no_nl(fd);
	}
}
