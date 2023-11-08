/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:22:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/08 14:59:34 by hunam            ###   ########.fr       */
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

int	len_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		i++;
	return (i);
}

void	free_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		free((char *)obj[i++]);
	free(obj);
}

bool	streq(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);

	return (s1_len == (int)ft_strlen(s2) && ft_strncmp(s1, s2, s1_len) == 0);
}
