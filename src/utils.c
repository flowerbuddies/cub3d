/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/20 18:41:24 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tiles_len(t_tile *tiles)
{
	int	i;

	i = 0;
	while (*tiles++)
		i++;
	return (i);
}

int	len_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		i++;
	return (i);
}

bool	streq(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);

	return (s1_len == (int)ft_strlen(s2) && ft_strncmp(s1, s2, s1_len) == 0);
}

int	open_file(char *filename)
{
	const int	fd = open(filename, O_RDONLY);

	if (fd == -1)
		error(NULL, NULL);
	return (fd);
}

char	*gnl_no_nl(int fd)
{
	char	*line;
	int		len;
	char	*new_line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (line[len - 1] != '\n')
		return (line);
	new_line = ft_substr(line, 0, len - 1);
	if (!new_line)
		error(NULL, NULL);
	free(line);
	return (new_line);
}

t_vec2	*vec2(double x, double y)
{
	t_vec2	*out;

	out = malloc(sizeof(t_vec2));
	if (!out)
		error(NULL, NULL);
	out->x = x;
	out->y = y;
	return (out);
}

t_vec2_int	*vec2_int(int x, int y)
{
	t_vec2_int	*out;

	out = malloc(sizeof(t_vec2_int));
	if (!out)
		error(NULL, NULL);
	out->x = x;
	out->y = y;
	return (out);
}

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}
