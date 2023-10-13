/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/13 17:15:47 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		param_error(NULL, NULL, NULL, NULL); //TODO: make sure strerror is working
	return (fd);
}

char	*gnl_no_nl(int fd, t_assets *assets)
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
	free(line);
	if (!new_line)
		param_error("Failed trimming new line", assets, NULL, NULL);
	return (new_line);
}
