/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/11 14:57:28 by marmulle         ###   ########.fr       */
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

void	parse(char *filename, t_assets *assets)
{
	int	fd;

	check_filename(filename);
	fd = open_file(filename);
	// ft_bzero(assets, sizeof(assets));
	ft_bzero(assets, 4 * sizeof(mlx_texture_t) + 2 * sizeof(int *));
	parse_params(fd, assets);






	if (close(fd) == -1)
		error(NULL, NULL);

	// while (get_next_line(fd))
	// {
	// 	/* code */
	// }

}
