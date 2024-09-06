/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:56:25 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/23 14:12:04 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_is_numeric(const char *str)
{
	const char	*temp;

	if (*str == '0')
		return (1);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			temp = str;
			while (*temp == ' ' || *temp == '\n')
				temp++;
			if (*temp == '\0')
				return (1);
			return (0);
		}
		str++;
	}
	return (1);
}

static unsigned int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static unsigned int	char_to_hex(t_game *game, char **tab)
{
	int	r;
	int	g;
	int	b;

	if (tab[0] && tab[1] && tab[2])
	{
		if (!ft_is_numeric(tab[0]) || !ft_is_numeric(tab[1]) || \
		!ft_is_numeric(tab[2]))
			return (ft_free_error("Error\nColor not number\n", game), 0);
		else
		{
			r = ft_atoi(tab[0]);
			if (r > 255 || r < 0)
				return (ft_free_error("Error\nHexaColor not exist\n", game), 0);
			g = ft_atoi(tab[1]);
			if (g > 255 || g < 0)
				return (ft_free_error("Error\nHexaColor not exist\n", game), 0);
			b = ft_atoi(tab[2]);
			if (b > 255 || b < 0)
				return (ft_free_error("Error\nHexaColor not exist\n", game), 0);
			return (rgb_to_hex(r, g, b));
		}
	}
	return (ft_free_error("Error\nHexaColor not exist\n", game), 0);
}

void	check_rgb(t_game *game, unsigned int *textures, char *line, int index)
{
	char	**temp;
	int		i;

	if (*textures != 256)
		ft_free_error("Error\nDouble identifiant\n", game);
	while (line[index] && line[index] == ' ')
		index++;
	if (!line[index] || line[index] == '\n')
		ft_free_error("Error\nMissing path\n", game);
	temp = ft_split(line + index, ',');
	*textures = char_to_hex(game, temp);
	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
	free(line);
}
