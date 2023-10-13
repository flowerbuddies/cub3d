/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:22:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 17:29:56 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// specific error handlers per module
// each module has directory e.g. /parser which contains error.c
// e.g. parser module has
//			param_error(char *message, char *line, char **parts)
//			map_error(char *message, t_map *map, t_tiles *tiles)

// maybe struct of func pointers
// typedef struct s_err
// {
// 	...	param();
// 	... map();
// }		t_err;
// if (map_error_has_occured)
// 	err.map("map failed", map, tiles);

void	map_error(char *message, t_ctx *ctx, t_tile *tiles, char *line)
{
	if (ctx)
	{
		free_assets(&ctx->assets);
		free_tilemap(&ctx->map);
	}
	if (tiles)
		free(tiles);
	if (line)
		free(line);
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	param_error(char *message, t_assets *assets, char *line, char **parts)
{
	if (assets)
		free_assets(assets);
	if (line)
		free(line);
	if (parts)
		free_2d((const char **) parts);
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	error_mlx(mlx_t *mlx, char *message)
{
	if (mlx)
		mlx_close_window(mlx);
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else if (mlx)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}
