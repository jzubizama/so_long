/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:03:32 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/29 12:12:50 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_ber(char *name)
{
	int		i;
	int		op;
	char	*term;

	i = 0;
	while (name[i])
		i++;
	term = &name[i - 4];
	if (!ft_strncmp(term, ".ber", 4))
	{
		op = open(name, O_RDONLY);
		if (op < 0)
			return (-1);
		close(op);
		return (0);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	int			len;

	if (argc != 2)
		return (1);
	if (ft_check_ber(argv[1]) < 0)
		return (3);
	len = ft_line_length(argv[1]);
	prog.map = ft_read_map(argv[1]);
	prog.map_size = ft_line_num(argv[1]);
	prog.pl_pos = ft_fill_pos(prog.map, prog.map_size);
	if (!ft_check_map(&prog, argv[1]))
		return (2);
	prog.mlx = mlx_init();
	prog.sprites = ft_def_sprites(prog.mlx);
	prog.window = ft_new_window(prog.mlx, prog.sprites.wall.size.x * len,
			prog.sprites.wall.size.y * prog.map_size, "so_long Josu");
	prog.sp_pos.x = 0;
	prog.sp_pos.y = 0;
	prog.nbr_mov = 0;
	ft_print_map(&prog);
	ft_printf("%i\n", prog.map_size);
	mlx_key_hook(prog.window.ref, *ft_input, &prog);
	mlx_hook(prog.window.ref, 17, 0, *ft_close, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
