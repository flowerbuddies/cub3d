/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/08 14:09:29 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "defs.h"
# include "fns.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

# define FOV .66
# define BIG_DOUBLE 1e30
# define DEADZONE 5
# define SECRET 0x2A2A2A

# define MINIMAP_SIZE .33
# define MINIMAP_VOID_COLOR 0xd8e993FF
# define MINIMAP_FLOOR_COLOR 0xfffefbFF
# define MINIMAP_WALL_COLOR 0xf7d0d5FF

#endif
