/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:30:45 by wheino            #+#    #+#             */
/*   Updated: 2025/07/09 18:52:13 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_vars *vars)
{
	int		y;
	int		x;
	t_point	current;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			current = project_iso(vars->map->points[y][x], vars);
			draw_neighbors(vars, x, y, current);
			x++;
		}
		y++;
	}
}

void	draw_neighbors(t_vars *vars, int x, int y, t_point current)
{
	t_point	neighbor;

	if (x + 1 < vars->map->width)
	{
		neighbor = project_iso(vars->map->points[y][x + 1], vars);
		draw_line(vars, current, neighbor, 0xFFFFFF);
	}
	if (y + 1 < vars->map->height)
	{
		neighbor = project_iso(vars->map->points[y + 1][x], vars);
		draw_line(vars, current, neighbor, 0xFFFFFF);
	}
}
