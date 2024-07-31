/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:31:09 by josu              #+#    #+#             */
/*   Updated: 2023/08/07 08:53:27 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Returns 1 if map is rectangular, 0 if not
int	ft_check_rect(char *path)
{
	int		op;
	char	buf[1];
	int		cont;
	int		len;

	op = open(path, O_RDONLY);
	cont = 0;
	len = ft_line_length(path);
	while (read(op, buf, 1))
	{
		if (buf[0] == '\n')
		{
			if (cont != len)
				return (0);
			else
				cont = -1;
		}
		cont++;
	}
	close (op);
	if (cont != len)
		return (0);
	return (1);
}

//Returns number of Coins if there is 1 'P', 1 'E' and 1 or more 'C'-- if not 0
int	ft_check_obj(char *path)
{
	int		op;
	char	buf[1];
	int		cont[3];

	op = open(path, O_RDONLY);
	cont[0] = 0;
	cont[1] = 0;
	cont[2] = 0;
	while (read(op, buf, 1))
	{
		if (buf[0] == 'P')
			cont[0]++;
		else if (buf[0] == 'E')
			cont[1]++;
		else if (buf[0] == 'C')
			cont[2]++;
		else if (buf[0] != '1' && buf[0] != '0' && buf[0] != '\n')
			return (0);
	}
	close (op);
	if (cont[0] == 1 && cont[1] == 1 && cont[2] >= 1)
		return (cont[2]);
	else
		return (0);
}

//recursive function to check the correct path
int	*ft_check_path_iter(char **map, int i, int j, int *cont)
{
	if (map[i][j] == 'C')
		cont[0]++;
	else if (map[i][j] == 'E')
		cont[1]++;
	map[i][j] = '1';
	if (map[i + 1][j] != '1')
		ft_check_path_iter(map, i + 1, j, cont);
	if (map[i][j + 1] != '1')
		ft_check_path_iter(map, i, j + 1, cont);
	if (map[i - 1][j] != '1')
		ft_check_path_iter(map, i - 1, j, cont);
	if (map[i][j - 1] != '1')
		ft_check_path_iter(map, i, j - 1, cont);
	return (cont);
}

//Returns 1 if there is a possible win
int	ft_check_path(char **map, t_vector pos, int coinNbr)
{
	int	cont[2];

	cont[0] = 0;
	cont[1] = 0;
	ft_check_path_iter(map, pos.y, pos.x, cont);
	if (cont[1] == 1 && cont[0] == coinNbr)
		return (1);
	else
		return (0);
}

//Makes all checks
int	ft_check_map(t_program *prog, char *path)
{
	int	coins;

	coins = ft_check_obj(path);
	if (!ft_check_wall(prog->map, prog->map_size, ft_line_length(path)))
	{
		write(1, "Error\nNot rounded by walls!\n", 28);
		return (0);
	}
	if (ft_check_rect(path) == 0)
	{
		write(1, "Error\nMap is not rectangular!\n", 30);
		return (0);
	}
	if (coins == 0)
	{
		write(1, "Error\nObjects are not correct!\n", 31);
		return (0);
	}
	if (!ft_check_path(prog->map, prog->pl_pos, coins))
	{
		write(1, "Error\nNo possible solution!\n", 28);
		return (0);
	}
	ft_reread_map(path, prog);
	return (1);
}
