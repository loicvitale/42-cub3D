/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:20:29 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/28 10:10:41 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	*ft_safe_calloc(size_t count, size_t size, char *error_message, \
t_game *game)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		printf("Error\nAllocating memory for : %s", error_message);
		if (game)
			ft_free(game);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

t_img	*get_texture(t_game *game, int flag)
{
	game->ray->angle = nor_angle(game->ray->angle);
	if (flag == 0)
	{
		if (game->ray->angle > M_PI / 2 && game->ray->angle < 3 * (M_PI / 2))
			return (game->textures->t_we);
		else
			return (game->textures->t_ea);
	}
	else
	{
		if (game->ray->angle > 0 && game->ray->angle < M_PI)
			return (game->textures->t_so);
		else
			return (game->textures->t_no);
	}
}

int	wall_hit(float x, float y, t_game *game)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= game->map->heightmap || x_m >= game->map->widthmap))
		return (0);
	if (game->map->map[y_m] && x_m <= (int)ft_strlen(game->map->map[y_m]))
		if (game->map->map[y_m][x_m] == '1')
			return (0);
	return (1);
}
