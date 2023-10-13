/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 17:17:57 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_filename(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		param_error("Invalid file name", NULL, NULL, NULL);
	if (ft_strlen(ext) != 4 || ft_strncmp(ext, ".cub\0", 4))
		param_error("Invalid file name", NULL, NULL, NULL);
}

void	parse(char *filename, t_ctx *ctx)
{
	int	fd;

	check_filename(filename);
	fd = open_file(filename);
	ft_bzero(&ctx->assets, sizeof(t_assets));
	parse_params(fd, &ctx->assets);
	parse_map(fd, &ctx);
	check_map_validity(ctx);
	if (close(fd) == -1)
		param_error(NULL, &ctx->assets, NULL, NULL); //TODO: make sure strerror is working
}
