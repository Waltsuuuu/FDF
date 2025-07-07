/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:23:52 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 23:27:02 by wheino           ###   ########.fr       */
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
	if (keycode == KEY_E)
	{
		vars->scale += 5;
		if (vars->scale < 1)
			vars->scale = 1;
	}
	if (keycode == KEY_Q)
	{
		vars->scale -= 5;
		if (vars->scale < 1)
			vars->scale = 1;
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		handle_arrow_key(keycode, vars);
	redraw(vars);
	return (0);
}

void	handle_arrow_key(int keycode, t_vars *vars)
{
	if (keycode == KEY_UP)
		vars->y_offset += 40;
	if (keycode == KEY_DOWN)
		vars->y_offset -= 40;
	if (keycode == KEY_LEFT)
		vars->x_offset += 40;
	if (keycode == KEY_RIGHT)
		vars->x_offset -= 40;
}

int	handle_x_click(t_vars *vars)
{
	free_and_destroy(vars);
	return (0);
}

void	redraw(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	ft_memset(vars->img_data, 0, vars->line_len * WIN_HEIGHT);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
