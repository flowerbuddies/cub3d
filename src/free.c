/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:27:38 by hunam             #+#    #+#             */
/*   Updated: 2023/11/06 16:10:28 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_assets(const t_assets *assets)
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
	if (player->plane)
		free(player->plane);
}

static void	free_raycast(const t_raycast *raycast)
{
	if (raycast->ray_dir)
		free(raycast->ray_dir);
	if (raycast->hit_pos)
		free(raycast->hit_pos);
	if (raycast->dda.side_dist)
		free(raycast->dda.side_dist);
	if (raycast->dda.delta_dist)
		free(raycast->dda.delta_dist);
	if (raycast->dda.step_dir)
		free(raycast->dda.step_dir);
	if (raycast->dda.cell)
		free(raycast->dda.cell);
	if (raycast->dda.is_vertical_side)
		free(raycast->dda.is_vertical_side);
}

void	free_ctx(void)
{
	const t_ctx	*ctx = get_ctx();

	if (ctx->mlx)
		mlx_terminate(ctx->mlx);
	free_assets(&ctx->assets);
	free_map(&ctx->map);
	free_player(&ctx->player);
	free_raycast(&ctx->raycast);
}
