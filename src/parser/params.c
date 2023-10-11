/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/11 15:38:07 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_texture(const char **parts, char *line)
{
	mlx_texture_t	*out;
	char			*newline;

	if (len_2d(parts) > 2 && !streq(parts[2], "\n")) //TODO:check `NO` but without map at the end
	{
		free_2d(parts);
		free(line);
		error(NULL, "Invalid parameter argument count");
	}
	newline = ft_strrchr(parts[1], '\n');
	if (newline)
		*newline = '\0';
	printf("text path: %s\n", parts[1]);  //TODO: rm
	out = mlx_load_png(parts[1]); //TODO:check `NO`
	if (!out)
	{
		free_2d(parts);
		free(line);
		error(NULL, "Cannot load texture");
	}
	return (out);
}

static int	*get_color(const char **parts, char *line)
{
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

	if (!parts)
		error(NULL, NULL);
	// TODO: check empty file (gnl returns NULL?)
	if (streq(parts[0], "NO"))
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
		free(line);
		free_2d(parts);
		error(NULL, "Invalid parameter identifier");
	}
	free_2d(parts);
}


void	parse_params(int fd, t_assets *assets)
{
	char	*line;
	char	*identifier;

	while (!are_params_satisfied(assets))
	{
		line = get_next_line(fd);
		if (!line)
			error(NULL, "Parameters not satisfied");
		identifier = line;
		while (*identifier == ' ')
			identifier++;
		printf("identifier: _%s_", identifier); //TODO: rm
		if (*identifier != '\n' && *identifier != '\0')
			parse_param(identifier, assets);
		free(line);
	}
}
