/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:12:50 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 10:53:34 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	image;

	image.ref = mlx_xpm_file_to_image(mlx, path, &image.size.x, &image.size.y);
	image.pixels = mlx_get_data_addr(image.ref, &image.bits_per_pixel,
			&image.line_size, &image.endian);
	return (image);
}

t_sprite	ft_def_sprites(void *mlx)
{
	t_sprite	sprites;

	sprites.wall = ft_new_sprite(mlx, "./sprites/Other/Walls/wall.xpm");
	sprites.black = ft_new_sprite(mlx, "./sprites/Other/Walls/black.xpm");
	sprites.player = ft_new_sprite(mlx, "./sprites/Pac-Man/pac_closed.xpm");
	sprites.pl_up = ft_new_sprite(mlx, "./sprites/Pac-Man/pac_semi_up.xpm");
	sprites.pl_right = ft_new_sprite(mlx,
			"./sprites/Pac-Man/pac_semi_right.xpm");
	sprites.pl_down = ft_new_sprite(mlx, "./sprites/Pac-Man/pac_semi_down.xpm");
	sprites.pl_left = ft_new_sprite(mlx, "./sprites/Pac-Man/pac_semi_left.xpm");
	sprites.exit = ft_new_sprite(mlx, "./sprites/Other/Portal/portal.xpm");
	sprites.collect = ft_new_sprite(mlx,
			"./sprites/Other/Pacdots/pacdot_food.xpm");
	return (sprites);
}
