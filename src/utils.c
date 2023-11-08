/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/08 14:40:30 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*safe_load_png(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (mlx_load_png(filename));
}

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}

void	error(mlx_t *mlx, char *message)
{
	ft_putstr_fd("Error\n", 2);
	if (mlx)
		mlx_close_window(mlx);
	if (message)
		ft_putstr_fd(message, 2);
	else if (mlx)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}
