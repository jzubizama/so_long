/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:12:57 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/30 12:09:24 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

int	ft_close(int key, void *param)
{
	//t_program *prog;

	//prog = (t_program *)param;
	(void)key;
	(void)param;
	//mlx_destroy_window(prog->mlx, prog->window.ref);
	/* if (prog->map)
		ft_free_map (prog->map, prog->map_size); */
	//system("leaks so_long");
	exit(0);
}

t_window	ft_new_window(void *mlx, int widht, int height, char *name)
{
	t_window	window;
	int			esc;

	esc = 53;
	window.ref = mlx_new_window(mlx, widht, height, name);
	window.size.x = widht;
	window.size.y = height;
	return (window);
}
