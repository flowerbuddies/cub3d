/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:36:17 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 16:13:32 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}


void	error(mlx_t *mlx, char *message)
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
