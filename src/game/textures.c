/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:21:33 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/28 09:43:59 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	load_texture(void *mlx, t_img *texture, char *file_path)
{
	texture->width = 0;
	texture->height = 0;
	texture->img_ptr = mlx_xpm_file_to_image(mlx, file_path, \
		&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		printf("Error\nFailed to load texture: %s\n", file_path);
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp, \
		&texture->size_line, &texture->endian);
}

void	init_textures(t_game *game)
{
	game->textures->t_no = ft_safe_calloc(sizeof(t_img), 1, "t_no", game);
	game->textures->t_so = ft_safe_calloc(sizeof(t_img), 1, "t_so", game);
	game->textures->t_we = ft_safe_calloc(sizeof(t_img), 1, "t_we", game);
	game->textures->t_ea = ft_safe_calloc(sizeof(t_img), 1, "t_ea", game);
	if (game->textures->t_no && game->textures->t_so
		&& game->textures->t_we && game->textures->t_ea)
	{
		load_texture(game->mlx, game->textures->t_no, game->textures->no);
		load_texture(game->mlx, game->textures->t_so, game->textures->so);
		load_texture(game->mlx, game->textures->t_we, game->textures->we);
		load_texture(game->mlx, game->textures->t_ea, game->textures->ea);
	}
	else
	{
		printf("Error\nFailed to allocate memory for texture structures\n");
		exit(EXIT_FAILURE);
	}
}
