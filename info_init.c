/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 08:50:28 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/29 09:58:25 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Rereads map information
void	ft_reread_map(char *path, t_program *prog)
{
	int		op;
	char	buf[1];
	char	**map;
	int		i;
	int		j;

	map = prog->map;
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
}

//Returns the length of the first line of file in "path"
int	ft_line_length(char *path)
{
	int		op;
	char	buf[1];
	int		cont;

	op = open(path, O_RDONLY);
	if (!op)
		exit(0);
	cont = 0;
	while (read(op, buf, 1) && buf[0] != '\n')
	{
		cont++;
	}
	close (op);
	return (cont);
}

//Returns the number of lines of file in "path"
int	ft_line_num(char *path)
{
	int		op;
	char	buf[1];
	int		cont;

	op = open(path, O_RDONLY);
	cont = 1;
	while (read(op, buf, 1))
	{
		if (buf[0] == '\n')
			cont++;
	}
	close (op);
	return (cont);
}

//Returns the player position information
t_vector	ft_fill_pos(char **map, int lines)
{
	int			i;
	int			j;
	t_vector	pos;

	i = 0;
	pos.x = 0;
	pos.y = 0;
	pos.aux = 0;
	while (i < lines)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

//Returns 1 if map is rounded by walls - 1 if not
int	ft_check_wall(char **map, int lines, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < lines)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if ((i == 0 || i == lines - 1) && map[i][j] != '1')
				return (0);
			if ((j == 0 || j == cols - 1) && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
