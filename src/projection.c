/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:51:20 by wheino            #+#    #+#             */
/*   Updated: 2025/06/25 18:55:58 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void init_bounds(double b[4])
{
    b[0] = 1e9;
    b[1] = -1e9;
    b[2] = 1e9;
    b[3] = -1e9;
}

static void scan_iso_bounds(t_vars *vars, double b[4])
{
    int     x;
    int     y;
    t_point p;
    t_point raw;

    y = 0;
    while (y < vars->map->height)
    {
        x = 0;
        while (x < vars->map->width)
        {
            raw = vars->map->points[y][x];
            
            raw.z *= Z_SCALE;
            p = project_iso(raw);
            if (p.x < b[0])
                b[0] = p.x;
            if (p.x > b[1])
                b[1] = p.x;
            if (p.y < b[2])
                b[2] = p.y;
            if (p.y > b[3])
                b[3] = p.y;
            x++;
        }
        y++;
    }
}

static void get_iso_bounds(t_vars *vars, double b[4])
{
    init_bounds(b);
    scan_iso_bounds(vars, b);
}

void scale_and_center(t_vars *vars)
{
    double  b[4];
    double  sx;
    double  sy;

    vars->zoom = 1.0;
    get_iso_bounds(vars, b);
    sx = (WIN_WIDTH - 2 * PADDING) / (b[1] - b[0]);
    sy = (WIN_HEIGHT - 2 * PADDING) / (b[3] - b[2]);
    if (sx < sy)
        vars->zoom = sx;
    else
        vars->zoom = sy;
    get_iso_bounds(vars, b);
    vars->offset_x = (WIN_WIDTH - (b[1] - b[0]) * vars->zoom) / 2
                   - b[0] * vars->zoom;
    vars->offset_y = (WIN_HEIGHT - (b[3] - b[2]) * vars->zoom) / 2
                   - b[2] * vars->zoom;
}

t_point project_scaled_iso(t_point pt, t_vars *vars)
{
    double  sx;
    double  sy;
    double  sz;
    t_point res;

    sx = pt.x * vars->zoom;
    sy = pt.y * vars->zoom;
    sz = pt.z * Z_SCALE * vars->zoom;
    res = project_iso((t_point){(int)sx, (int)sy, (int)sz});
    res.x += vars->offset_x;
    res.y += vars->offset_y;
    return (res);
}

/* basic isometric projection */
t_point project_iso(t_point pt)
{
    t_point res;
    double  cos_a;
    double  sin_a;

    cos_a = cos(ISO_ANGLE);
    sin_a = sin(ISO_ANGLE);
    res.x = (pt.x - pt.y) * cos_a;
    res.y = (pt.x + pt.y) * sin_a - pt.z;
    res.z = pt.z;
    return (res);
}
