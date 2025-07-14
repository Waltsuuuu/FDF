/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:02:36 by wheino            #+#    #+#             */
/*   Updated: 2025/07/14 18:21:19 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_iso(t_point point, t_vars *vars)
{
	t_point	proj;
	float	x;
	float	y;
	float	z;

	x = point.x * vars->scale;
	y = point.y * vars->scale;
	z = point.z * Z_SCALE * vars->scale;
	proj.x = (int)((x - y) * cosf(ISO_ANGLE)) + vars->x_offset;
	proj.y = (int)((x + y) * sinf((ISO_ANGLE)) - z) + vars->y_offset;
	proj.z = point.z;
	return (proj);
}
