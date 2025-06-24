/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:49:10 by wheino            #+#    #+#             */
/*   Updated: 2025/06/24 16:01:06 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Draw the grid
void	draw_grid(t_vars *vars)
{
	int		x, y;
	t_point	a, b;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			a = project_iso(vars->map->points[y][x]);
			a.x += vars->offset_x;
			a.y += vars->offset_y;

			if (x < vars->map->width - 1)
			{
				b = project_iso(vars->map->points[y][x + 1]);
				b.x += vars->offset_x;
				b.y += vars->offset_y;
				draw_line(vars, a.x, a.y, b.x, b.y, 0xFFFFFF);
			}
			if (y < vars->map->height - 1)
			{
				b = project_iso(vars->map->points[y + 1][x]);
				b.x += vars->offset_x;
				b.y += vars->offset_y;
				draw_line(vars, a.x, a.y, b.x, b.y, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
}
// Places pixel at x, y, with a color.
void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
    	return;
	dst = vars->img_data + (y * vars->line_len + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_line(t_line *line, int x0, int y0, int x1, int y1)
{
	line->dx = abs(x1 - x0);
	line->dy = -abs(y1 - y0);
	if (x0 < x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (y0 < y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
	t_line line;

	init_line(&line, x0, y0, x1, y1);
	while (1)
	{
		put_pixel(vars, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			y0 += line.sy;
		}
	}
}
