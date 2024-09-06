/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:02:16 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/28 13:09:11 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	ft_free_textures(t_game *game)
{
	free(game->textures->no);
	free(game->textures->t_no);
	free(game->textures->so);
	free(game->textures->t_so);
	free(game->textures->we);
	free(game->textures->t_we);
	free(game->textures->ea);
	free(game->textures->t_ea);
	free(game->textures);
}

int	ft_mlx_hook(t_game *game)
{
	ft_free_message("Window Closed\n\n", game);
	return (0);
}

void	ft_free_error(char *message, t_game *game)
{
	perror(message);
	if (game)
		ft_free(game);
	exit(EXIT_FAILURE);
}

void	ft_free_message(char *message, t_game *game)
{
	printf("%s", message);
	if (game)
		ft_free(game);
	exit(EXIT_FAILURE);
}

void	ft_free(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = -1;
		while (i++ < game->map->heightmap)
			free(game->map->map[i]);
		free(game->map->map);
		free(game->map);
	}
	if (game->textures)
		ft_free_textures(game);
	game->map = NULL;
	if (game->win_init == 1)
		mlx_destroy_window(game->mlx, game->win);
	free(game->ray);
	free(game->player);
	free(game);
}
