/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:31:36 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/13 14:39:35 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	init_struct(t_game *game)
{
	game->map = ft_safe_calloc(sizeof(t_map), 1, \
		"init_struct -> game.map\n", game);
	game->player->pdir = '\0';
	game->map->heightmap = -1;
	game->textures = ft_safe_calloc(sizeof(t_textures), 1, \
		"init_struct -> game.textures\n", game);
	game->textures->no = NULL;
	game->textures->so = NULL;
	game->textures->ea = NULL;
	game->textures->we = NULL;
	game->textures->f = 256;
	game->textures->c = 256;
}

void	find_identifiant(t_game *game, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (check_path(game, &game->textures->no, line, 2));
	if (ft_strnstr(line, "SO", 2))
		return (check_path(game, &game->textures->so, line, 2));
	if (ft_strnstr(line, "WE", 2))
		return (check_path(game, &game->textures->we, line, 2));
	if (ft_strnstr(line, "EA", 2))
		return (check_path(game, &game->textures->ea, line, 2));
	if (ft_strnstr(line, "F", 1))
		return (check_rgb(game, &game->textures->f, line, 1));
	if (ft_strnstr(line, "C", 1))
		return (check_rgb(game, &game->textures->c, line, 1));
	ft_free_error("Error\nUnknow textures\n", game);
}

int	size_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	check_map(t_game *game, char **argv)
{
	char	*readmap;

	if (!(check_ext(argv[1], ".cub")))
		ft_free_error("Error\nInvalid extension\n", game);
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd < 0)
		ft_free_error("Error\nCannot be open\n", game);
	game->player = ft_safe_calloc(sizeof(t_player), 1, "player\n", game);
	init_struct(game);
	while (1)
	{
		readmap = get_next_line(game->fd);
		if (!check_line(game, readmap))
			break ;
	}
	close (game->fd);
	if (!game->map->map)
		ft_free_error("Error\nMap empty\n", game);
	if (!game->player->pdir)
		ft_free_error("Error\nPlayer missing\n", game);
	init_the_player(game);
	is_map_surronded(game);
	return (1);
}
