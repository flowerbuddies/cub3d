/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:27:38 by hunam             #+#    #+#             */
/*   Updated: 2023/10/13 22:05:43 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		free((char *)obj[i++]);
	free(obj);
}

static void	free_params(const t_assets *assets)
{
	if (assets->north)
		mlx_delete_texture(assets->north);
	if (assets->south)
		mlx_delete_texture(assets->south);
	if (assets->east)
		mlx_delete_texture(assets->east);
	if (assets->west)
		mlx_delete_texture(assets->west);
	if (assets->ceiling)
		free(assets->ceiling);
	if (assets->floor)
		free(assets->floor);
}

static void	free_map(const t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(map->tiles[i++]);
	free(map->tiles);
}

static void	free_player(const t_player *player)
{
	if (player->dir)
		free(player->dir);
	if (player->pos)
		free(player->pos);
}

void	free_ctx(void)
{
	const t_ctx	*ctx = get_ctx();

	free_params(&ctx->assets);
	free_map(&ctx->map);
	free_player(&ctx->player);
}
