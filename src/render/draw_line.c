/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:49:30 by wheino            #+#    #+#             */
/*   Updated: 2025/07/05 22:08:19 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
	t_line	line;
	
	init_line(&line, x0, y0, x1, y1);
	while (1)
	{
		put_pixel(vars, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
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

void	init_line(t_line *line, int x0, int y0, int x1, int y1)
{
	line->dx = abs(x1 - x0);
	line->dy = -abs(y1 -y0);
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
