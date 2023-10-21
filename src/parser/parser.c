/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/21 19:35:43 by hunam            ###   ########.fr       */
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
