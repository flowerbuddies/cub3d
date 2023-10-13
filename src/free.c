/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:27:38 by hunam             #+#    #+#             */
/*   Updated: 2023/10/13 20:17:09 by hunam            ###   ########.fr       */
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

void	free_params(void)
{
	const t_assets	*assets = &get_ctx()->assets;

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

void	free_map(void)
{
	const t_map	*map = &get_ctx()->map;
	int			i;

	free_params();
	i = 0;
	while (i < map->height)
		free(map->tiles[i++]);
	free(map->tiles);
}

t_free	*free_the(void)
{
	static t_free	free = {free_params, free_map};

	return (&free);
}
