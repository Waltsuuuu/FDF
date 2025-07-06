/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:02:36 by wheino            #+#    #+#             */
/*   Updated: 2025/07/06 16:21:56 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_iso(t_point point, t_vars *vars)
{
	t_point proj;
	float	x;
	float	y;
	float	z;

	calculate_scale_and_offset(vars);
	// Scaling coords into "pixel-space".
	// If "scale" is 20, then we are...
	// Turning "1 unit in map coords" into "20 units in pixel coordinates"
	x = point.x * vars->scale;
	y = point.y * vars->scale;
	z = point.z * Z_SCALE * vars->scale;

	//Isometric x coordinate
	proj.x = (int)((x - y) * cosf(ISO_ANGLE)) + vars->x_offset;

	//Isometric y coordinate
	proj.y = (int)((x + y) * sinf((ISO_ANGLE)) - z) + vars->y_offset;
	
	//Preserve original z
	proj.z = point.z;

	//Return the projected point
	return (proj);
}

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
