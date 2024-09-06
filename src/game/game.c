/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:00:44 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/31 12:15:32 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	init_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
		&game->endian);
}

static void	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	init_image(game);
}

static int	render_loop(t_game *game)
{
	draw_floor_and_ceiling(game);
	raycasting(game);
	draw_minimap(game, 0);
	render(game);
	mlx_do_sync(game->mlx);
	return (0);
}

void	init_the_player(t_game *game)
{
	if (!game->player)
	{
		game->player = ft_safe_calloc(sizeof(t_player), 1, "t_player\n", game);
		if (!game->player)
			ft_free_error("Error\nAllocating player\n", game);
	}
	if (game->player->pdir == 'N')
		game->player->direction = 3.0 * M_PI / 2.0;
	if (game->player->pdir == 'S')
		game->player->direction = M_PI / 2.0;
	if (game->player->pdir == 'W')
		game->player->direction = M_PI;
	if (game->player->pdir == 'E')
		game->player->direction = 0;
	game->player->fov = (FIELD_OF_VIEW * M_PI) / 180;
}

void	ft_init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_free_error("Error\nMLX init don't work\n\n", game);
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3D");
	if (!game->win)
		ft_free_error("Error\nProblem with window\n\n", game);
	init_image(game);
	init_textures(game);
	game->win_init = 1;
	game->ray = ft_safe_calloc(sizeof(t_ray), 1, "ray\n", game);
	mlx_hook(game->win, 2, 1L << 0, ft_key_hook, game);
	mlx_hook(game->win, 17, 0, ft_mlx_hook, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
}
