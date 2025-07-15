/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:50:30 by wheino            #+#    #+#             */
/*   Updated: 2025/07/14 22:02:48 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		file_check;

	if (argc != 2)
	{
		ft_printf("ERROR: Needs 2 args. Second arg must be map file!\n");
		return (EXIT_FAILURE);
	}
	file_check = check_file_type(argv[1]);
	if (file_check == ERROR)
	{
		ft_printf("ERROR: Map must be in .fdf format!\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&vars, sizeof vars);
	vars.map = open_and_parse_map(argv[1]);
	if (!vars.map)
		return (EXIT_FAILURE);
	if ((init_mlx(&vars, WIN_WIDTH, WIN_HEIGHT, "FDF") == ERROR))
		free_and_destroy(&vars);
	calculate_scale_and_offset(&vars);
	draw_map(&vars);
	mlx_function_calls(&vars);
	return (EXIT_SUCCESS);
}

int	check_file_type(char *path)
{
	char	*type_start;

	type_start = ft_strchr(path, '.');
	if (!type_start)
		return (ERROR);
	if (ft_strncmp(type_start, ".fdf", 4) == 0)
		return (OK);
	else
		return (ERROR);
}

void	mlx_function_calls(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_key_hook(vars->win, handle_keypress, vars);
	mlx_hook(vars->win, 17, 0, handle_x_click, vars);
	mlx_loop(vars->mlx);
}
