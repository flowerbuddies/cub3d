/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/11 17:37:32 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_texture(const char **parts, char *line)
{
	mlx_texture_t	*out;

	if (len_2d(parts) != 2)
	{
		free_2d(parts);
		free(line);
		error(NULL, "Invalid parameter argument count");
	}
	// TODO:check `NO` but without map at the end
	out = mlx_load_png(parts[1]);
	if (!out)
	{
		free_2d(parts);
		free(line);
		error(NULL, "Cannot load texture"); // TODO: fix error message
	}
	free_2d(parts);
	free(line);
	return (out);
}

static int	*get_color(const char **parts, char *line)
{
	free_2d(parts);
	free(line);
	return (malloc(sizeof(int)));
}

static bool	are_params_satisfied(t_assets *assets)
{
	return (assets->north && assets->south && assets->east && assets->west
		&& assets->ceiling && assets->floor);
}

static void	parse_param(char *line, t_assets *assets)
{
	const char	**parts = (const char **)ft_split(line, ' ');

	// TODO: check empty file (gnl returns NULL?)
	if (!parts)
		error(NULL, NULL);
	else if (!*parts)
		(free_2d(parts), free(line));
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
		(free_2d(parts), free(line));
		error(NULL, "Invalid parameter identifier/Parameters not satisfied");
	}
}

void	parse_params(int fd, t_assets *assets)
{
	char	*raw_line;
	char	*line;

	while (!are_params_satisfied(assets))
	{
		raw_line = get_next_line(fd);
		if (!raw_line)
			error(NULL, "Parameters not satisfied");
		line = ft_substr(raw_line, 0, ft_strlen(raw_line) - 1);
		free(raw_line);
		parse_param(line, assets);
	}
}
