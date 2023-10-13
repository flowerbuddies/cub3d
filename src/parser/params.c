/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 17:21:40 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_texture(
		const char **parts, char *line, t_assets *assets)
{
	mlx_texture_t	*out;

	if (len_2d(parts) != 2)
		param_error("Invalid NO/SO/EA/WE parameter argument count", 
			assets, line, parts);
	// TODO:check `NO` but without map at the end
	out = mlx_load_png(parts[1]);
	if (!out)
		param_error("Cannot load texture", assets, line, parts); // TODO: fix error message (mark: seems fine?)
	return (out);
}

static int	*channels_to_color(char **channels)
{
	const int	r = ft_atoi(channels[0]);
	const int	g = ft_atoi(channels[1]);
	const int	b = ft_atoi(channels[2]);
	int			*out;

	free_2d((const char **)channels);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (NULL);
	out = malloc(sizeof(int));
	if (!out)
		return (NULL);
	*out = r << 24 | g << 16 | b << 8;
	return (out);
}

static int	*get_color(const char **parts, char *line, t_assets *assets)
{
	char	**channels;
	int		*color;

	if (len_2d(parts) != 2)
		param_error("Invalid C/F argument count", assets, line, parts);
	channels = ft_split(parts[1], ',');
	if (!channels)
		param_error("Could not split color channels", assets, line, parts);
	if (len_2d((const char **)channels) != 3)
	{
		free_2d((const char **)channels);
		param_error("Invalid number of color channels", assets, line, parts);
	}
	color = channels_to_color(channels);
	if (!color)
		param_error("Invalid color channel range", assets, line, parts);
	return (color);
}

static void	parse_param(char *line, t_assets *assets)
{
	const char	**parts = (const char **)ft_split(line, ' ');

	// TODO: check empty file (gnl returns NULL?)
	if (!parts)
		param_error("Failed to split line", assets, line, NULL);
	else if (!*parts)
		;
	else if (streq(parts[0], "NO"))
		assets->north = get_texture(parts, line, assets);
	else if (streq(parts[0], "SO"))
		assets->south = get_texture(parts, line, assets);
	else if (streq(parts[0], "EA"))
		assets->east = get_texture(parts, line, assets);
	else if (streq(parts[0], "WE"))
		assets->west = get_texture(parts, line, assets);
	else if (streq(parts[0], "F"))
		assets->floor = get_color(parts, line, assets);
	else if (streq(parts[0], "C"))
		assets->ceiling = get_color(parts, line, assets);
	else
		param_error("Invalid parameter identifier/Parameters not satisfied",
			assets, line, parts); //TODO: can params not be satisfied here despite parse_params error message?
	(free_2d(parts), free(line));
}

void	parse_params(int fd, t_assets *assets)
{
	char	*line;

	while (!(assets->north && assets->south && assets->east && assets->west
			&& assets->ceiling && assets->floor))
	{
		line = gnl_no_nl(fd, assets);
		if (!line)
			param_error("Parameters not satisfied", assets, NULL, NULL);
		parse_param(line, assets);
	}
}
