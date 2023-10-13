/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:42:19 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 17:32:11 by marmulle         ###   ########.fr       */
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

static void	check_vertical(t_ctx *ctx, int x, int y)
{
	int	next_len;

	if (y == 0)
		map_error("Unclosed map on upper edge", ctx, NULL, NULL);
	if (y == ctx->map.height)
		map_error("Unclosed map on lower edge", ctx, NULL, NULL);
	next_len = get_row_len(&ctx->map, y - 1);
	if (x >= next_len)
		map_error("Unclosed map due to short upper row", ctx, NULL, NULL);
	next_len = get_row_len(&ctx->map, y + 1);
	if (x >= next_len)
		map_error("Unclosed map due to short lower row", ctx, NULL, NULL);
	if (ctx->map.tilemap[y - 1][x] == BOUNDS || ctx->map.tilemap[y + 1][x] == BOUNDS)
		map_error("Out of bounds inside map", ctx, NULL, NULL);
}

static void	check_horizontal(t_ctx *ctx, int x, int y)
{
	int	row_len;

	if (x == 0)
		map_error("Unclosed map on left edge", ctx, NULL, NULL);
	row_len = get_row_len(&ctx->map, y);
	if (x + 1 == row_len)
		map_error("Unclosed map on right edge", ctx, NULL, NULL);
	if (ctx->map.tilemap[y][x - 1] == BOUNDS || ctx->map.tilemap[y][x + 1] == BOUNDS)
		map_error("Out of bounds inside map", ctx, NULL, NULL);
}

void	check_map_validity(t_ctx *ctx)
{
	t_tile	tile;
	bool	found_player;
	int		y;
	int		x;

	found_player = false;
	y = -1;
	while (++y < ctx->map.height)
	{
		x = -1;
		while (++x < ctx->map.width && ctx->map.tilemap[y][x] != _END_TILE)
		{
			tile = ctx->map.tilemap[y][x];
			if (tile == FLOOR || tile == PLAYER)
			{
				if (tile == PLAYER && found_player)
					map_error("Too many spawn points", ctx, NULL, NULL);
				else if (tile == PLAYER && !found_player)
					found_player = true;
				check_vertical(ctx, x, y);
				check_horizontal(ctx, x, y);
			}
		}
	}
}
