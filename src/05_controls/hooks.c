/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:23:52 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 22:45:24 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		free_and_destroy(vars);
		exit(0);
	}
	if (keycode == KEY_UP)
	{
		vars->scale += 5;
		mlx_clear_window(vars->mlx, vars->win);
		ft_memset(vars->img_data, 0, vars->line_len * WIN_HEIGHT);
		draw_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	if (keycode == KEY_DOWN)
	{
		vars->scale -= 5;
		mlx_clear_window(vars->mlx, vars->win);
		ft_memset(vars->img_data, 0, vars->line_len * WIN_HEIGHT);
		draw_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	return (0);
}

int	handle_x_click(t_vars *vars)
{
	free_and_destroy(vars);
	return (0);
}
