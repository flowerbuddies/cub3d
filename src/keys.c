/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:17:46 by hunam             #+#    #+#             */
/*   Updated: 2023/10/17 19:51:46 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_hook(t_ctx *ctx)
{
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		(free_ctx(), exit(0));
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_MINUS))
		resize_minimap(ctx, -50);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_EQUAL))
		resize_minimap(ctx, 50);
}
