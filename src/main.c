/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:50:30 by wheino            #+#    #+#             */
/*   Updated: 2025/07/05 22:49:42 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if(argc != 2)
		return 0;
	ft_bzero(&vars, sizeof vars);
	vars.map = open_and_parse_map(argv[1]);
	if (!vars.map)
		return (EXIT_FAILURE);
	if ((init_mlx(&vars, WIN_WIDTH, WIN_HEIGHT, "FDF") == ERROR))
		return (free_and_destroy(&vars));
	print_map(vars.map); // Testing only
	draw_map(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    mlx_loop(vars.mlx);
	free_and_destroy(&vars);
	return (EXIT_SUCCESS);
}
