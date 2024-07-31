/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:01:38 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/30 12:08:47 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include"./minilibx/mlx.h"
# include<stdio.h>
# include<unistd.h>
# include<fcntl.h>
# include"./libft/libft.h"

/* vector with an x and y, aux to save direction */
typedef struct s_vector
{
	int	x;
	int	y;
	int	aux;
}				t_vector;

/* A pointer to the window and its size */
typedef struct s_window {
	void		*ref;
	t_vector	size;
}				t_window;

/* The 4 values that define a color */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

/* all info needed for an image */
typedef struct s_image {
	void		*ref;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_sprite
{
	t_image		wall;
	t_image		black;
	t_image		collect;
	t_image		player;
	t_image		pl_up;
	t_image		pl_right;
	t_image		pl_down;
	t_image		pl_left;
	t_image		exit;
}				t_sprite;

typedef struct s_program
{
	void		*mlx;
	t_window	window;
	t_sprite	sprites;
	t_vector	sp_pos;
	t_vector	pl_pos;
	char		**map;
	int			map_size;
	int			nbr_mov;
}				t_program;

t_window	ft_new_window(void *mlx, int widht, int height, char *name);
t_sprite	ft_def_sprites(void *mlx);
void		ft_print_map(t_program *prog);
int			ft_input(int key, void *param);
int			ft_close(int key, void *param);
int			ft_check_rect(char *path);
int			ft_check_map(t_program *prog, char *path);
char		**ft_read_map(char *path);

void		ft_reread_map(char *path, t_program *prog);
int			ft_line_length(char *path);
int			ft_line_num(char *path);
t_vector	ft_fill_pos(char **map, int lines);
int			ft_check_wall(char **map, int lines, int cols);

void		ft_update(int x, int y, t_program *prog);

void		ft_free_map(char **map, int lines);

#endif