/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:42:32 by hunam             #+#    #+#             */
/*   Updated: 2023/11/06 14:39:47 by marmulle         ###   ########.fr       */
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
			(free_ctx(), error(NULL, "No map found"));
		if (line[0])
			return (line);
		free(line);
	}
}

static void	append_tiles(t_map *map, t_tile *tiles)
{
	t_tile	**new_tiles;
	int		i;

	if (!map->tiles)
	{
		map->tiles = malloc(sizeof(t_tile *));
		if (!map->tiles)
			error(NULL, NULL);
		map->tiles[0] = tiles;
		map->height = 1;
		return ;
	}
	map->height++;
	new_tiles = malloc(sizeof(t_tile *) * map->height);
	if (!new_tiles)
		error(NULL, NULL);
	i = -1;
	while (++i < map->height - 1)
		new_tiles[i] = map->tiles[i];
	new_tiles[i] = tiles;
	free(map->tiles);
	map->tiles = new_tiles;
}

static void	set_player(t_player *player, char dir, int x, int y)
{
	if (player->pos)
		(free_ctx(), error(NULL, "Too many spawn positions"));
	player->pos = vec2f(x + .5, y + .5);
	if (dir == 'N')
	{
		player->dir = vec2f(0, -1);
		player->plane = vec2f(FOV, 0);
	}
	else if (dir == 'S')
	{
		player->dir = vec2f(0, 1);
		player->plane = vec2f(FOV, 0);
	}
	else if (dir == 'E')
	{
		player->dir = vec2f(1, 0);
		player->plane = vec2f(0, FOV);
	}
	else
	{
		player->dir = vec2f(-1, 0);
		player->plane = vec2f(0, FOV);
	}
}

static t_tile	*get_tiles(t_ctx *ctx, char *line)
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
		tiles[i] = FLOOR;
		if (line[i] == ' ')
			tiles[i] = VOID;
		else if (line[i] == '1')
			tiles[i] = WALL;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			set_player(&ctx->player, line[i], i, ctx->map.height);
		else if (line[i] != '0')
			(free(line), free(tiles), free_ctx(), error(NULL, "Wrong symbol"));
	}
	tiles[i] = _END_TILE;
	if (len > ctx->map.width)
		ctx->map.width = len;
	return (tiles);
}

void	parse_map(int fd, t_ctx *ctx)
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
			(free(line), free_ctx(), error(NULL, "Empty line inside the map"));
		else
			append_tiles(&ctx->map, get_tiles(ctx, line));
		free(line);
		line = gnl_no_nl(fd);
	}
}
