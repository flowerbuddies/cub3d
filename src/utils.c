/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 14:43:51 by marmulle         ###   ########.fr       */
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

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}
