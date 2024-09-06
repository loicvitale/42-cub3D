/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:49:27 by lvitale           #+#    #+#             */
/*   Updated: 2024/05/28 10:01:37 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static int	all_textures_done(t_game *game)
{
	if (game->textures->no && game->textures->so && game->textures->we
		&& game->textures->ea && game->textures->f != 256 \
		&& game->textures->c != 256)
		return (1);
	return (0);
}

static void	check_map_line(t_game *game, char *line, size_t size_line)
{
	int	i;

	i = -1;
	if (size_line > game->map->widthmap)
		game->map->widthmap = size_line;
	if (!line[0] || line[0] == '\n')
		ft_free_error("Error\nMap invalid\n", game);
	while (++i < size_line - 1 && line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
		{
			if (!game->player->pdir && (line[i] == 'N' || line[i] == 'S' \
				|| line[i] == 'E' || line[i] == 'W'))
			{
				game->player->pdir = line[i];
				game->player->pos_x = i * TILE_SIZE;
				game->player->pos_y = game->map->heightmap * TILE_SIZE;
			}
			else
			{
				printf("Error\nUnknow symbol : %c\n", line[i]);
				ft_free_error("", game);
			}
		}
	}
}

int	check_ext(char *str, char *ext)
{
	int	i;
	int	size_str;
	int	size_ext;

	size_str = ft_strlen(str);
	size_ext = ft_strlen(ext);
	i = 1;
	while (i <= size_ext)
	{
		if (str[size_str - i] != ext[size_ext - i])
			return (0);
		i++;
	}
	return (1);
}

void	check_path(t_game *game, char **textures, char *line, int index)
{
	char	*cleaned_path;
	int		len;

	if (*textures)
		ft_free_error("Error\nDouble identifiant\n", game);
	while (line[index] && line[index] == ' ')
		index++;
	if (!line[index] || line[index] == '\n')
		ft_free_error("Error\nMissing path\n", game);
	*textures = ft_strdup(line + index);
	if (*textures == NULL)
		ft_free_error("Error\nMemory allocation failed\n", game);
	cleaned_path = *textures;
	len = ft_strlen(cleaned_path);
	while (len > 0 && (cleaned_path[len - 1] == ' '
			|| cleaned_path[len - 1] == '\n'))
	{
		cleaned_path[len - 1] = '\0';
		len--;
	}
	free(line);
}

int	check_line(t_game *game, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	if (line[0] == '\n' && !game->map->map)
		return (free(line), 1);
	if (!all_textures_done(game))
		find_identifiant(game, line);
	else
	{
		i = -1;
		game->map->heightmap++;
		temp = ft_safe_calloc(sizeof(char *), game->map->heightmap + 1, \
			"check_line -> temp\n", game);
		temp[game->map->heightmap] = NULL;
		while (i++ < game->map->heightmap - 1)
			temp[i] = game->map->map[i];
		temp[i] = line;
		if (game->map->map)
			free(game->map->map);
		game->map->map = temp;
		check_map_line(game, temp[i], ft_strlen(temp[i]));
	}
	return (1);
}
