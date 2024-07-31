/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:36:22 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/29 09:38:23 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Checks if there is coin in the map
int	ft_check_coin(t_program *prog)
{
	int	i;
	int	j;

	i = 0;
	while (i < prog->map_size)
	{
		j = 0;
		while (prog->map[i][j] != '\0')
		{
			if (prog->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

//Movement condition checker
int	ft_move_check(t_program *prog, int dx, int dy)
{
	int	exit;
	int	x;
	int	y;

	exit = 1;
	y = prog->pl_pos.y + dy;
	x = prog->pl_pos.x + dx;
	if (prog->map[y][x] == '1' || (!exit && prog->map[y][x] == 'E'))
		return (0);
	else
		return (1);
}

void	ft_check_exit(t_program *prog)
{
	int	x;
	int	y;

	y = prog->pl_pos.y;
	x = prog->pl_pos.x;
	if (prog->map[y][x] == 'E' && ft_check_coin(prog))
		ft_close(0, prog);
}

//Selecting case of key pressed
void	ft_check_key(int key, t_program *prog, void **ref)
{
	if ((key == 124 || key == 2) && ft_move_check(prog, 1, 0))
	{
		ft_update(1, 0, prog);
		*ref = prog->sprites.pl_right.ref;
	}
	else if ((key == 123 || key == 0) && ft_move_check(prog, -1, 0))
	{
		ft_update(-1, 0, prog);
		*ref = prog->sprites.pl_left.ref;
	}
	else if ((key == 125 || key == 1) && ft_move_check(prog, 0, 1))
	{
		ft_update(0, 1, prog);
		*ref = prog->sprites.pl_down.ref;
	}
	else if ((key == 126 || key == 13) && ft_move_check(prog, 0, -1))
	{
		ft_update(0, -1, prog);
		*ref = prog->sprites.pl_up.ref;
	}
	else if (key == 53)
		ft_close(0, prog);
}

/* Any functon that you hook with the key event must be like this:
* Recibing and int for the code of the key pressed
* and a void pointer in case you need to recibe someting */
int	ft_input(int key, void *param)
{
	void		*ref;
	t_program	*prog;

	prog = (t_program *)param;
	if (prog->map[prog->pl_pos.y][prog->pl_pos.x] == 'E')
		ref = prog->sprites.exit.ref;
	else
		ref = prog->sprites.black.ref;
	mlx_put_image_to_window(prog->mlx, prog->window.ref, ref,
		prog->pl_pos.x * prog->sprites.wall.size.x,
		prog->pl_pos.y * prog->sprites.wall.size.y);
	ref = prog->sprites.player.ref;
	ft_check_key(key, prog, &ref);
	mlx_put_image_to_window(prog->mlx, prog->window.ref, ref,
		prog->pl_pos.x * prog->sprites.wall.size.x,
		prog->pl_pos.y * prog->sprites.wall.size.y);
	if (prog->map[prog->pl_pos.y][prog->pl_pos.x] == 'C')
		prog->map[prog->pl_pos.y][prog->pl_pos.x] = '0';
	ft_check_exit(prog);
	return (0);
}
