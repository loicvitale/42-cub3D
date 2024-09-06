/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:51:23 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/28 12:58:28 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

static float	get_h_inter(t_game *game, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(game->player->pos_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player->pos_x + (h_y - game->player->pos_y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0)
		|| (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray->horiz_x = h_x;
	game->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - game->player->pos_x, 2) \
		+ pow(h_y - game->player->pos_y, 2)));
}

static float	get_v_inter(t_game *game, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(game->player->pos_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = game->player->pos_y + (v_x - game->player->pos_x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0)
		|| (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray->vert_x = v_x;
	game->ray->vert_y = v_y;
	return (sqrt(pow(v_x - game->player->pos_x, 2) \
		+ pow(v_y - game->player->pos_y, 2)));
}

static void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;
	t_img	*texture;

	game->ray->distance *= cos(nor_angle(game->ray->angle \
		- game->player->direction));
	wall_h = (TILE_SIZE / game->ray->distance) * ((W_WIDTH / 2) \
		/ tan(game->player->fov / 2));
	b_pix = (W_HEIGHT / 2) + (wall_h / 2);
	t_pix = (W_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > W_HEIGHT)
		b_pix = W_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_textured_line(game, t_pix, b_pix, wall_h);
}

void	raycasting(t_game *game)
{
	int		i;
	double	h_inter;
	double	v_inter;

	game->ray->angle = game->player->direction - (game->player->fov / 2);
	i = -1;
	while (++i < W_WIDTH)
	{
		game->ray->flag = 0;
		game->ray->ray_id = i;
		game->ray->start_x = game->player->pos_x;
		game->ray->start_y = game->player->pos_y;
		h_inter = get_h_inter(game, nor_angle(game->ray->angle));
		v_inter = get_v_inter(game, nor_angle(game->ray->angle));
		if (v_inter <= h_inter)
			game->ray->distance = v_inter;
		else
		{
			game->ray->distance = h_inter;
			game->ray->flag = 1;
		}
		render_wall(game, game->ray->ray_id);
		game->ray->angle += (game->player->fov / W_WIDTH);
	}
}
