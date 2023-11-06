/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 14:43:36 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_filename(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		error(NULL, "Invalid file name");
	if (ft_strlen(ext) != 4 || ft_strncmp(ext, ".cub\0", 4))
		error(NULL, "Invalid file name");
}

static int	open_file(char *filename)
{
	const int	fd = open(filename, O_RDONLY);

	if (fd == -1)
		error(NULL, NULL);
	return (fd);
}

void	parse(char *filename, t_ctx *ctx)
{
	int	fd;

	check_filename(filename);
	fd = open_file(filename);
	parse_params(fd, &ctx->assets);
	parse_map(fd, ctx);
	check_map_validity(&ctx->map);
	if (close(fd) == -1)
		error(NULL, NULL);
}

t_tile	get_tile(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (VOID);
	if (x < 0 || x >= get_tiles_len(map->tiles[y]))
		return (VOID);
	return (map->tiles[y][x]);
}
