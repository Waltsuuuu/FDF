/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:49:30 by wheino            #+#    #+#             */
/*   Updated: 2025/07/08 22:22:54 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_vars *vars, t_point start, t_point end, int color)
{
	t_line	line;

	line.x0 = start.x;
	line.y0 = start.y;
	line.x1 = end.x;
	line.y1 = end.y;
	init_line(&line);
	while (1)
	{
		put_pixel(vars, line.x0, line.y0, color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			line.x0 += line.sx;
		}
	}
}

void	init_line(t_line *line)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = -abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}
