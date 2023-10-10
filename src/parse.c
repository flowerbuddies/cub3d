/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/10 18:51:09 by marmulle         ###   ########.fr       */
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

static bool	are_params_satisfied(t_assets *assets)
{
	return (assets->north && assets->south && assets->east && assets->west
		&& assets->ceiling && assets->floor); //TODO: init all of those to NULL
}

static bool	parse_param(char *line, t_assets *assets)
{
	const char	**parts = ft_split(line, ' ');

	if (!parts)
		error(NULL, NULL);
	// TODO: check empty file (gnl returns NULL?)
	if (streq(parts[0], "NO"))
		assets->north = get_texture(parts[1]);
	else if (streq(parts[0], "SO"))
		assets->south = get_texture(parts[1]);
	else if (streq(parts[0], "EA"))
		assets->east = get_texture(parts[1]);
	else if (streq(parts[0], "WE"))
		assets->west = get_texture(parts[1]);
	else if (streq(parts[0], "F"))
		assets->floor = get_color(parts);
	else if (streq(parts[0], "C"))
		assets->ceiling = get_color(parts);
	else
	{
		free(line);
		free_2d(parts);
		error(NULL, "Invalid parameter identifier");
	}
	free_2d(parts);
}


static void	parse_params(int fd, t_assets *assets)
{
	char	*line;

	while (!are_params_satisfied(assets))
	{
		line = get_next_line(fd);
		if (!line)
			error(NULL, "Parameters not satisfied");
		parse_param(line, assets);
		free(line);
	}
}

void	parse(char *filename, t_assets *assets)
{
	int	fd;

	check_filename(filename);
	fd = open_file(filename);
	parse_params(fd, assets);







	if (close(fd) == -1)
		error(NULL, NULL);

	// while (get_next_line(fd))
	// {
	// 	/* code */
	// }

}
