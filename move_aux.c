/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:45:23 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:48:24 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

//Update moving values
void	ft_update(int x, int y, t_program *prog)
{
	prog->pl_pos.x += x;
	prog->pl_pos.y += y;
	prog->nbr_mov++;
	ft_printf("%i\n", prog->nbr_mov);
}
