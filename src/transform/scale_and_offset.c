/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_and_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:44:29 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 16:45:26 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_scale_and_offset(t_vars *vars)
{
	int		width;
	int		height;
	float	span;
	float	mid_x;
	float	mid_y;

	width = vars->map->width - 1;
	height = vars->map->height - 1;
	span = (width + height);
	vars->scale = (int)fminf((float)WIN_WIDTH / (span * cosf(ISO_ANGLE)),
			(float)WIN_HEIGHT / (span * sinf(ISO_ANGLE)));
	if (vars->scale < 1)
		vars->scale = 1;
	mid_x = ((width - height) * cosf(ISO_ANGLE) * vars->scale * 0.5f);
	mid_y = ((width + height) * sinf(ISO_ANGLE) * vars->scale * 0.5f);
	vars->x_offset = WIN_WIDTH / 2 - (int)mid_x;
	vars->y_offset = WIN_HEIGHT / 2 - (int)mid_y;
}
