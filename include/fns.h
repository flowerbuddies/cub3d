/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/11/06 16:26:23 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FNS_H
# define FNS_H

# include "cub3d.h"

// main.c
t_ctx		*get_ctx(void);

// utils.c
int			get_tiles_len(t_tile *tiles);
int			len_2d(const char **obj);
bool		streq(const char *s1, const char *s2);
char		*gnl_no_nl(int fd);
void		clear_img(mlx_image_t *img);

// hooks.c
void		keys_hook(t_ctx *ctx);
void		cursor_hook(t_ctx *ctx);

// background.c
void		init_background(t_ctx *ctx);

// free.c
void		free_ctx(void);

// raycast/dda.c
t_vec2f		*vec2f(double x, double y);
t_vec2i		*vec2i(int x, int y);
double		dda(t_ctx *ctx);

// raycast/raycast.c
void		init_raycast(t_ctx *ctx);
void		draw_raycast(t_ctx *ctx);

// raycast/draw.c
void		draw_hit(t_ctx *ctx);
void		draw_vert_strips(t_ctx *ctx, int x, double ray_len,
				double x_mapping);

// parser/*.c
void		parse(char *filename, t_ctx *ctx);
void		parse_params(int fd, t_assets *assets);
void		parse_map(int fd, t_ctx *ctx);
void		check_map_validity(t_map *map);
t_tile		get_tile(t_map *map, int x, int y);

// parser/utils.c
int			get_tiles_len(t_tile *tiles);
int			len_2d(const char **obj);
void		free_2d(const char **obj);
bool		streq(const char *s1, const char *s2);
char		*gnl_no_nl(int fd);

// utils.c
void		clear_img(mlx_image_t *img);
void		error(mlx_t *mlx, char *message);

// minimap/*.c
void		init_minimap(t_ctx *ctx);
void		draw_minimap(t_ctx *ctx);

#endif
