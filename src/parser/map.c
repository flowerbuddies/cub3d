/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:42:32 by hunam             #+#    #+#             */
/*   Updated: 2023/10/13 17:23:00 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_nl(int fd, t_ctx *ctx)
{
	char	*line;

	while (42)
	{
		line = gnl_no_nl(fd, &ctx->assets);
		if (!line)
		{
			// TODO: handle leaks
			map_error("No map found", ctx, NULL, NULL);
		}
		if (line[0])
			return (line);
		free(line);
	}
}

static void	init_tilemap(t_ctx *ctx, t_tile *tiles, char *line)
{
	ctx->map.tilemap = malloc(sizeof(t_tile *));
	if (!ctx->map.tilemap)
		map_error("Failed to allocate tilemap", ctx, tiles, line);
	ctx->map.tilemap[0] = tiles;
	ctx->map.height = 1;
}

static void	append_tiles(t_ctx *ctx, t_tile *tiles, char *line)
{
	t_tile	**new_tilemap;
	int		i;

	if (!ctx->map.tilemap)
		return (init_tilemap(ctx, tiles, line));
	ctx->map.height++;
	new_tilemap = malloc(sizeof(t_tile *) * ctx->map.height);
	if (!new_tilemap)
		map_error("Failed to allocate tilemap", ctx, tiles, line);
	i = -1;
	while (++i < ctx->map.height - 1)
		new_tilemap[i] = ctx->map.tilemap[i];
	new_tilemap[i] = tiles;
	free(ctx->map.tilemap);
	ctx->map.tilemap = new_tilemap;
}

static void	update_tilemap_width(t_map *map, int len)
{
	if (len > map->width)
		map->width = len;
}

static t_tile	*get_tiles(t_ctx *ctx, char *line)
{
	t_tile		*tiles;
	int			i;
	const int	len = ft_strlen(line);

	tiles = malloc(sizeof(t_tile) * (len + 1));
	if (!tiles)
		map_error("Failed to allocate tiles", ctx, NULL, line);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			tiles[i] = BOUNDS;
		else if (line[i] == '0')
			tiles[i] = FLOOR;
		else if (line[i] == '1')
			tiles[i] = WALL;
		else if (line[i] == 'N' || line[i] == 'S' 
			|| line[i] == 'E' || line[i] == 'W')
			tiles[i] = PLAYER;
		else
			map_error("Bad character in the map", ctx, NULL, line);
	}
	tiles[i] = _END_TILE;
	update_tilemap_width(&ctx->map, len);
	return (tiles);
}

void	parse_map(int fd, t_ctx *ctx)
{
	char	*line;
	bool	seen_empty_line;

	line = skip_nl(fd, ctx);
	seen_empty_line = false;
	while (line)
	{
		if (!line[0])
			seen_empty_line = true;
		else if (seen_empty_line)
			map_error("Empty line inside the map", ctx, NULL, line);
		else
			append_tiles(ctx, get_tiles(ctx, line), line);
		free(line);
		line = gnl_no_nl(fd, &ctx->assets);
	}
}
