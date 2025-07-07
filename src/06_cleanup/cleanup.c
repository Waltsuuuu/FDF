/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:06:51 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 21:51:04 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_destroy(t_vars *vars)
{
	if (vars->img != NULL)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	if (vars->map != NULL)
		free_map(vars->map);
	exit(0);
}
