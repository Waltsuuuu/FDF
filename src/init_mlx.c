/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:45:00 by wheino            #+#    #+#             */
/*   Updated: 2025/07/06 15:42:07 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_mlx(t_vars *vars, int width, int height, char *title)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ERROR);
	vars->win = mlx_new_window(vars->mlx, width, height, title);
	if (!vars->win)
		return (ERROR);
	vars->img = mlx_new_image(vars->mlx, width, height);
	if (!vars->img)
		return (ERROR);
	vars->img_data = mlx_get_data_addr(vars->img, &vars->bpp,
			&vars->line_len, &vars->endian);
	if (!vars->img_data)
		return (ERROR);
	return (OK);
}
