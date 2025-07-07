/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:23:52 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 21:56:47 by wheino           ###   ########.fr       */
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
	return (0);
}

int	handle_x_click(t_vars *vars)
{
	free_and_destroy(vars);
	return (0);
}
