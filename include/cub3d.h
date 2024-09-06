/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:01:40 by jhouyet           #+#    #+#             */
/*   Updated: 2024/05/31 12:19:17 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx/mlx.h"
# include "libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>

# define W_WIDTH 1650
# define W_HEIGHT 900 
# define TILE_SIZE 64
# define FIELD_OF_VIEW 60
# define ROTATION_SPEED 0.1
# define PLAYER_SPEED 0.2
# define MINIMAP_SCALE 4
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define MAX_VIEW_DISTANCE 10.0

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	float		direction;
	char		pdir;
	float		fov;
}				t_player;

typedef struct s_ray
{
	int		ray_id;
	double	start_x;
	double	start_y;
	double	angle;
	int		flag;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
}	t_ray;

typedef struct s_map
{
	char	**map;
	int		heightmap;
	int		widthmap;
}				t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_textures
{
	t_img			*t_no;
	t_img			*t_so;
	t_img			*t_we;
	t_img			*t_ea;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned int	f;
	unsigned int	c;
}				t_textures;

typedef struct s_game
{
	int			fd;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			win_init;
	t_map		*map;
	t_textures	*textures;
	t_player	*player;
	t_ray		*ray;
}				t_game;

/* minimap.c */
void			draw_minimap(t_game *game, float y);

/* hooks.c */
int				ft_key_hook(int key, t_game *game);

/* game.c */
void			ft_init_game(t_game *game);
void			init_the_player(t_game *game);

/* exit.c */
int				ft_mlx_hook(t_game *game);
void			ft_free_error(char *message, t_game *game);
void			ft_free_message(char *message, t_game *game);
void			ft_free(t_game *game);

/* core_map.c */
void			find_identifiant(t_game *game, char *line);
int				size_line(char *line);
int				check_map(t_game *game, char **argv);

/* wall_map.c */
int				is_map_surronded(t_game *game);

/* check_map.c */
int				check_ext(char *str, char *ext);
void			check_path(t_game *game, char **textures, char *line, \
					int index);
int				check_line(t_game *game, char *line);

/* color.c */
void			check_rgb(t_game *game, unsigned int *textures, char *line, \
					int index);

/* utils.c */
void			*ft_safe_calloc(size_t count, size_t size, char *msg, \
					t_game *game);
float			nor_angle(float angle);
int				unit_circle(float angle, char c);
t_img			*get_texture(t_game *game, int flag);
int				wall_hit(float x, float y, t_game *game);

/* draw.c */
void			put_pixel_to_image(t_game *game, int x, int y, int color);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			draw_textured_line(t_game *game, int t_pix, int b_pix, \
					double wall_h);
void			draw_floor_and_ceiling(t_game *game);

/* raycasting.c */
void			raycasting(t_game *game);

/* textures.c */
void			init_textures(t_game *game);

#endif