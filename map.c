/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:33:38 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/29 09:52:28 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

//Frees memory allocated for map
void	ft_free_map(char **map, int lines)
{
	int		i;

	i = 0;
	while (i < lines)
	{
		free (map[i]);
		i++;
	}
	free(map);
}

//Allocate memory for the map size (2D array)
char	**ft_alloc_map(char *path)
{
	char	**map_buf;
	int		lines;
	int		i;

	lines = ft_line_num(path);
	map_buf = malloc(sizeof(char *) * (lines));
	if (!map_buf)
		return (NULL);
	map_buf[lines] = NULL;
	i = 0;
	while (i < lines)
	{
		map_buf[i] = malloc(sizeof(char) * (ft_line_length(path) + 1));
		if (!map_buf[i])
		{
			while (--i >= 0)
				free (map_buf[i]);
			free (map_buf);
			return (NULL);
		}
		i++;
	}
	return (map_buf);
}

//Returns ta 2D array filled with map information
char	**ft_read_map(char *path)
{
	int		op;
	char	buf[1];
	char	**map;
	int		i;
	int		j;

	map = ft_alloc_map(path);
	op = open(path, O_RDONLY);
	i = 0;
	j = 0;
	while (read(op, buf, 1))
	{
		if (buf[0] == '\n')
		{
			map[i][j] = '\0';
			i++;
			j = 0;
			continue ;
		}
		map[i][j] = buf[0];
		j++;
	}
	map[i][j] = '\0';
	return (map);
}

void	ft_check_print(t_program *prog, int i, int j)
{
	if (prog->map[i][j] == '1')
		mlx_put_image_to_window(prog->mlx, prog->window.ref,
			prog->sprites.wall.ref, prog->sp_pos.x, prog->sp_pos.y);
	else if (prog->map[i][j] == '0')
		mlx_put_image_to_window(prog->mlx, prog->window.ref,
			prog->sprites.black.ref, prog->sp_pos.x, prog->sp_pos.y);
	else if (prog->map[i][j] == 'P')
		mlx_put_image_to_window(prog->mlx, prog->window.ref,
			prog->sprites.player.ref, prog->sp_pos.x, prog->sp_pos.y);
	else if (prog->map[i][j] == 'C')
		mlx_put_image_to_window(prog->mlx, prog->window.ref,
			prog->sprites.collect.ref, prog->sp_pos.x, prog->sp_pos.y);
	else if (prog->map[i][j] == 'E')
		mlx_put_image_to_window(prog->mlx, prog->window.ref,
			prog->sprites.exit.ref, prog->sp_pos.x, prog->sp_pos.y);
}

//Prints the map in window
void	ft_print_map(t_program *prog)
{
	int	i;
	int	j;

	i = 0;
	while (i < prog->map_size)
	{
		j = 0;
		while (prog->map[i][j] != '\0')
		{
			ft_check_print(prog, i, j);
			prog->sp_pos.x += prog->sprites.exit.size.x;
			j++;
		}
		prog->sp_pos.x = 0;
		prog->sp_pos.y += prog->sprites.wall.size.y;
		i++;
	}
}
