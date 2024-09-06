/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:26:46 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/28 13:01:59 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	put_pixel_to_image(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= W_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= W_HEIGHT)
		return ;
	put_pixel_to_image(game, x, y, color);
}

static double	get_x_o(t_img	*texture, t_game *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->horiz_x * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vert_y * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

void	draw_textured_line(t_game *game, int t_pix, int b_pix, double wall_h)
{
	double		x_o;
	double		y_o;
	double		factor;
	uint32_t	*arr;
	t_img		*texture;

	texture = get_texture(game, game->ray->flag);
	arr = (uint32_t *)texture->addr;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (t_pix - (W_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(game, game->ray->ray_id, t_pix, \
			(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	draw_floor_and_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < W_HEIGHT / 2)
	{
		x = -1;
		while (++x < W_WIDTH)
			put_pixel_to_image(game, x, y, game->textures->f);
	}
	y--;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			put_pixel_to_image(game, x, y, game->textures->c);
	}
}
