/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:57:13 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/28 12:55:54 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	right_move(t_game *game, float x, float y, char dir)
{
	float	temp;

	if (dir)
	{
		game->player->pdir = dir;
		init_the_player(game);
	}
	game->player->pos_x = x;
	game->player->pos_y = y;
	return (1);
}

static int	moove_up_down(t_game *game, float x, float y, int key)
{
	double	dx;
	double	dy;
	int		coef;

	x = game->player->pos_x;
	y = game->player->pos_y;
	if (key == 13)
		coef = 1;
	else
		coef = -1;
	dx = coef * (cos(game->player->direction) * PLAYER_SPEED) * TILE_SIZE;
	dy = coef * (sin(game->player->direction) * PLAYER_SPEED) * TILE_SIZE;
	x += dx;
	y += dy;
	if (game->map->map[(int)(y + dy) / TILE_SIZE] \
		[(int)(x + dx) / TILE_SIZE] == '1')
		return (1);
	if (game->map->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == '1'
		|| !(right_move(game, x, y, '\0')))
		return (0);
	return (1);
}

static int	moove_left_right(t_game *game, float x, float y, int key)
{
	double	dx;
	double	dy;
	int		coef;

	x = game->player->pos_x;
	y = game->player->pos_y;
	if (key == 2)
		coef = 1;
	else
		coef = -1;
	dx = coef * (cos(game->player->direction + M_PI / 2) \
		* PLAYER_SPEED) * TILE_SIZE;
	dy = coef * (sin(game->player->direction + M_PI / 2) \
		* PLAYER_SPEED) * TILE_SIZE;
	x += dx;
	y += dy;
	if (game->map->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == '1'
		|| !(right_move(game, x, y, '\0')))
		return (0);
	return (1);
}

static int	rotate_left_right(t_game *game, int key)
{
	if (key == 123)
		game->player->direction -= ROTATION_SPEED;
	else
		game->player->direction += ROTATION_SPEED;
	return (1);
}

int	ft_key_hook(int key, t_game *game)
{
	int	works;

	if (key == 53)
		ft_free_message("Window Closed\n\n", game);
	if (key == 13 || key == 1)
		works = moove_up_down(game, 0, 0, key);
	if (key == 0 || key == 2)
		works = moove_left_right(game, 0, 0, key);
	if (key == 123 || key == 124)
		works = rotate_left_right(game, key);
	return (0);
}
