/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:45:00 by wheino            #+#    #+#             */
/*   Updated: 2025/06/24 15:45:31 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Remember to switch printfs to ft_printfs

int	init_mlx(t_vars *vars, int width, int height, char *title)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		printf("mlx init failed\n");
		return (0);
	}
	vars->win = mlx_new_window(vars->mlx, width, height, title);
	if (!vars->win)
	{
		printf("window init failed\n");
		return (0);
	}
	vars->img = mlx_new_image(vars->mlx, width, height);
	if (!vars->img)
	{
		printf("img init failed\n");
		return (0);
	}
	vars->img_data = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len, &vars->endian); // Pointer to the first byte of the image pixel data
	if (!vars->img_data)
	{
		printf("img_data failed\n");
		return (0);
	}
	return (1);
}
