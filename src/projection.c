/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:02:36 by wheino            #+#    #+#             */
/*   Updated: 2025/07/05 21:23:00 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_iso(t_point point, t_vars *vars)
{
	t_point proj;
	float	x;
	float	y;
	float	z;

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