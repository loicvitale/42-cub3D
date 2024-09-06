/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:49:24 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/23 13:04:31 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	is_a_wall(t_game *game, int i, int y)
{
	if (i < 0 || i > game->map->heightmap)
		return (0);
	if (y < 0 || y > game->map->widthmap)
		return (0);
	if (game->map->map[i][y] != '0')
		return (0);
	return (1);
}

static void	is_walled(t_game *game, int i, int y)
{
	if (is_a_wall(game, i, y - 1) || is_a_wall(game, i, y + 1))
		ft_free_error("Error\nMap not surrounded\n", game);
	if (is_a_wall(game, i - 1, y) || is_a_wall(game, i + 1, y))
		ft_free_error("Error\nMap not surrounded\n", game);
}

static void	fill_map(t_game *game, char ***map)
{
	char	*temp;
	int		i;
	int		y;

	i = -1;
	while (++i <= game->map->heightmap)
	{
		if (ft_strlen(game->map->map[i]) < game->map->widthmap)
		{
			temp = ft_safe_calloc(sizeof(char), game->map->widthmap, \
				"fill_map -> temp\n", game);
			ft_strlcpy(temp, game->map->map[i], \
				size_line(game->map->map[i]) + 1);
			y = ft_strlen(temp);
			while (y < game->map->widthmap - 1)
				temp[y++] = ' ';
			temp[y] = '\n';
			free(game->map->map[i]);
			game->map->map[i] = ft_strdup(temp);
			free(temp);
		}
	}
}

int	is_map_surronded(t_game *game)
{
	int	i;
	int	y;

	i = -1;
	fill_map(game, &game->map->map);
	while (++i <= game->map->heightmap)
	{
		y = 0;
		while (y < game->map->widthmap)
		{
			if (game->map->map[i][y] == ' ')
				is_walled(game, i, y);
			if (i == 0 || y == game->map->widthmap || y == 0 \
				|| i == game->map->heightmap)
				if (is_a_wall(game, i, y))
					ft_free_error("Error\nMap not surrounded \n", game);
			y++;
		}
	}
	return (0);
}
