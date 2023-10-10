/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/10 18:30:38 by marmulle         ###   ########.fr       */
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

static bool	parse_param(char **parts, t_assets *assets)
{
	const char	*ids = {"NO", "SO", "EA", "WE", "C", "F", "\n"};
	int			i;

	i = -1;
	while (++i < 7 && !streq(parts[0], ids[i]))
		;
	if (i == 7)
		return false; //TODO
	if (ids == NO)
		no_handling()
	ele if (ids == NO)
		no_handling()
	else if (ids == NO)
		no_handling()
}


static void	parse_params(int fd, t_assets *assets)
{
	char	*line;
	char	*parts;

	while (!are_params_satisfied(assets))
	{
		line = get_next_line(fd);
		if (!line)
			error(NULL, "Parameters not satisfied");
		parts = ft_split(line, ' ');
		if (!parts)
			error(NULL, NULL);
		else if (parts[0])
			parse_param(parts, assets);
		free(parts); //TODO: 2d
		free(line);
	}
	// if (are_params_satisfied(assets))
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
