/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/12 01:44:47 by hunam            ###   ########.fr       */
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
		error(NULL, NULL);
	return (fd);
}

int	error(mlx_t *mlx, char *message)
{
	if (mlx)
		mlx_close_window(mlx);
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else if (mlx)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
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
