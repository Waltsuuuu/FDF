/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:29:51 by wheino            #+#    #+#             */
/*   Updated: 2025/07/05 21:36:01 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	int		bytes_per_pixel;
	int		offset;
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	bytes_per_pixel = vars->bpp / 8;
	offset = (y * vars->line_len) + (x * bytes_per_pixel);
	dst = vars->img_data + offset;
	*(unsigned int *)dst = color;
}
