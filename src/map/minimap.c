/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 08:51:05 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/23 15:06:49 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	draw_square(t_game *game, float x, float y, int color)
{
	float	dy;
	float	dx;

	dy = -1;
	while (++dy < MINIMAP_SCALE)
	{
		dx = -1;
		while (++dx < MINIMAP_SCALE)
			put_pixel_to_image(game, MINIMAP_OFFSET_X + x * MINIMAP_SCALE + dx,
				MINIMAP_OFFSET_Y + y * MINIMAP_SCALE + dy, color);
	}
}

static void	loop_minimap(t_game *game, int start_x, int start_y, float y)
{
	int		color;
	float	x;

	x = start_x - 1;
	while (++x < start_x + 20)
	{
		if (x < 0 || x >= game->map->widthmap - 1
			|| y < 0 || y >= game->map->heightmap + 1)
			color = 0xCCCCCC;
		else if (game->map->map[(int)y][(int)x] == '1'
			|| game->map->map[(int)y][(int)x] == ' ')
			color = 0x000000;
		else if ((int)(game->player->pos_x / TILE_SIZE) == x
			&& (int)(game->player->pos_y / TILE_SIZE) == y)
			color = 0xFF0000;
		else
			color = 0xFFFFFF;
		draw_square(game, (x - start_x) * 1, (y - start_y) * 1, color);
	}
}

static void	draw_border(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x <= MINIMAP_OFFSET_X * MINIMAP_SCALE)
		put_pixel_to_image(game, MINIMAP_OFFSET_X + x, MINIMAP_OFFSET_Y, \
			0x000000);
	x = -1;
	while (++x <= MINIMAP_OFFSET_X * MINIMAP_SCALE)
		put_pixel_to_image(game, MINIMAP_OFFSET_X + x, MINIMAP_OFFSET_Y \
			+ MINIMAP_OFFSET_X * MINIMAP_SCALE, 0x000000);
	y = -1;
	while (++y <= MINIMAP_OFFSET_Y * MINIMAP_SCALE)
		put_pixel_to_image(game, MINIMAP_OFFSET_X, MINIMAP_OFFSET_Y \
			+ y, 0x000000);
	y = -1;
	while (++y <= MINIMAP_OFFSET_Y * MINIMAP_SCALE)
		put_pixel_to_image(game, MINIMAP_OFFSET_X + MINIMAP_OFFSET_Y \
			* MINIMAP_SCALE, MINIMAP_OFFSET_Y + y, 0x000000);
}

void	draw_minimap(t_game *game, float y)
{
	int		color;
	int		start_x;
	int		start_y;
	int		map_x;
	int		map_y;

	start_x = (int)(game->player->pos_x / TILE_SIZE) - 20 / 2;
	start_y = (int)(game->player->pos_y / TILE_SIZE) - 20 / 2;
	y = start_y - 1;
	while (++y < start_y + 20)
		loop_minimap(game, start_x, start_y, y);
	draw_border(game);
}
