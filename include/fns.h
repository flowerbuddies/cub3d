/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:51 by marmulle          #+#    #+#             */
/*   Updated: 2023/10/23 18:54:55 by marmulle         ###   ########.fr       */
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
int			open_file(char *filename);
char		*gnl_no_nl(int fd);
t_vec2		*vec2(double x, double y);
t_vec2_int	*vec2_int(int x, int y);
void		clear_img(mlx_image_t *img);

// hooks.c
void		keys_hook(t_ctx *ctx);
void		cursor_hook(double xpos, double ypos, t_ctx *ctx);

// background.c
void		init_background(t_ctx *ctx);

// error.c
void		error(mlx_t *mlx, char *message);

// free.c
void		free_2d(const char **obj);
void		free_ctx(void);

// raycast/*.c
void		draw_raycast(t_ctx *ctx);
void		init_raycast(t_ctx *ctx);
double		dda(t_ctx *ctx);
t_vec2		*get_hit_pos(t_vec2 *pos, t_vec2 *ray_dir, double ray_len);

// parser/*.c
void		parse(char *filename, t_ctx *ctx);
void		parse_params(int fd, t_assets *assets);
void		parse_map(int fd, t_ctx *ctx);
void		check_map_validity(t_map *map);
t_tile		get_tile(t_map *map, int x, int y);

// minimap/*.c
void		init_minimap(t_ctx *ctx);
void		draw_minimap(t_ctx *ctx);

#endif
