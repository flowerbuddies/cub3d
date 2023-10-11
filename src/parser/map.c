/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:42:32 by hunam             #+#    #+#             */
/*   Updated: 2023/10/12 01:54:06 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_nl(int fd)
{
	char	*line;

	while (42)
	{
		line = gnl_no_nl(fd);
		if (!line)
		{
			// TODO: handle leaks
			error(NULL, "No map found");
		}
		if (line[0])
			return (line);
		free(line);
	}
}

static void	append(bool ***arr, bool *el)
{
	bool	**out;
	int		i;

	i = 0;
	while ((*arr)[i])
		i++;
	out = malloc(sizeof(bool *) * (i + 2));
	if (!out)
		error(NULL, NULL);
	i = -1;
	while ((*arr)[++i])
		out[i] = (*arr)[i];
	out[i++] = el;
	out[i] = NULL;
	free(*arr);
	*arr = out;
}

static bool	*parse_line(char *line)
{
	bool	*walls_line;
	int		i;

	walls_line = malloc(sizeof(bool) * ft_strlen(line));
	i = -1;
	while (line[++i])
	{
		walls_line[i] = false;
		if (line[i] == '1')
			walls_line[i] = true;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			// TODO: handle player vector/pos
		}
		else if (line[i] != '0' && line[i] != ' ')
		{
			// TODO: handle leaks
			error(NULL, "Bad character in the map");
		}
	}
	return (walls_line);
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	bool	seen_empty_line;

	line = skip_nl(fd);
	seen_empty_line = false;
	map->walls = malloc(sizeof(bool *));
	if (!map->walls)
		error(NULL, NULL);
	map->walls[0] = NULL;
	while (line)
	{
		if (!line[0])
			seen_empty_line = true;
		else if (seen_empty_line)
			error(NULL, "Empty line inside the map");
		else
			append(&map->walls, parse_line(line));
		free(line);
		line = gnl_no_nl(fd);
	}
}
