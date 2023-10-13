/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 20:34:50 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_texture(const char **parts, char *line)
{
	mlx_texture_t	*out;

	if (len_2d(parts) != 2)
	{
		(free_the()->params(), free_2d(parts), free(line));
		error(NULL, "Invalid NO/SO/EA/WE parameter argument count");
	}
	out = mlx_load_png(parts[1]);
	if (!out)
	{
		(free_the()->params(), free_2d(parts), free(line));
		error(NULL, "Cannot load texture");
	}
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
		error(NULL, NULL);
	*out = r << 24 | g << 16 | b << 8;
	return (out);
}

static int	*get_color(const char **parts, char *line)
{
	char	**channels;
	int		*color;

	if (len_2d(parts) != 2)
	{
		(free_the()->params(), free_2d(parts), free(line));
		error(NULL, "Invalid C/F parameter argument count");
	}
	channels = ft_split(parts[1], ',');
	if (!channels)
		error(NULL, NULL);
	if (len_2d((const char **)channels) != 3)
	{
		(free_2d((const char **)channels), free_the()->params(), free_2d(parts),
			free(line));
		error(NULL, "Invalid number of color channels");
	}
	color = channels_to_color(channels);
	if (!color)
	{
		(free_the()->params(), free_2d(parts), free(line));
		error(NULL, "Invalid color channel range");
	}
	return (color);
}

static void	parse_param(char *line, t_assets *assets)
{
	const char	**parts = (const char **)ft_split(line, ' ');

	if (!parts)
		error(NULL, NULL);
	else if (!*parts)
		(void)parts;
	else if (streq(parts[0], "NO"))
		assets->north = get_texture(parts, line);
	else if (streq(parts[0], "SO"))
		assets->south = get_texture(parts, line);
	else if (streq(parts[0], "EA"))
		assets->east = get_texture(parts, line);
	else if (streq(parts[0], "WE"))
		assets->west = get_texture(parts, line);
	else if (streq(parts[0], "F"))
		assets->floor = get_color(parts, line);
	else if (streq(parts[0], "C"))
		assets->ceiling = get_color(parts, line);
	else
	{
		(free_the()->params(), free_2d(parts), free(line));
		error(NULL, "Invalid parameter identifier/Parameters not satisfied");
	}
	(free_2d(parts), free(line));
}

void	parse_params(int fd, t_assets *assets)
{
	char	*line;

	while (!(assets->north && assets->south && assets->east && assets->west
			&& assets->ceiling && assets->floor))
	{
		line = gnl_no_nl(fd);
		if (!line)
			error(NULL, "Parameters not satisfied");
		parse_param(line, assets);
	}
}
