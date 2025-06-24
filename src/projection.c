/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:51:20 by wheino            #+#    #+#             */
/*   Updated: 2025/06/24 15:52:34 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_2d(t_point p, t_vars *vars)
{
	t_point projected;

	projected.x = p.x * TILE_SIZE + vars->offset_x;
	projected.y = p.y * TILE_SIZE + vars->offset_y;
	projected.z = p.z;
	return (projected);
}

t_point project_iso(t_point p)
{
	t_point res;
	double angle = 0.523599; // ~30 degrees

	double x = p.x * TILE_SIZE;
	double y = p.y * TILE_SIZE;
	double z = p.z * Z_SCALE;


	res.x = (x - y) * cos(angle);
	res.y = (x + y) * sin(angle) - z;
	res.z = p.z;
	return res;
}

void calculate_offset(t_vars *vars)
{
    int x, y;
    double min_x = 1e9, max_x = -1e9;
    double min_y = 1e9, max_y = -1e9;
    t_point p;

    for (y = 0; y < vars->map->height; y++)
    {
        for (x = 0; x < vars->map->width; x++)
        {
            p = project_iso(vars->map->points[y][x]);
            if (p.x < min_x) min_x = p.x;
            if (p.x > max_x) max_x = p.x;
            if (p.y < min_y) min_y = p.y;
            if (p.y > max_y) max_y = p.y;
        }
    }

    vars->offset_x = (WIN_WIDTH - (max_x - min_x)) / 2 - min_x;
    vars->offset_y = (WIN_HEIGHT - (max_y - min_y)) / 2 - min_y;
}