/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:51:20 by wheino            #+#    #+#             */
/*   Updated: 2025/06/26 02:14:32 by wheino           ###   ########.fr       */
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

void get_iso_bounds(t_vars *vars, double b[4])
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
    // --- compute grid center ---
    double cx = (vars->map->width  - 1) * 0.5;
    double cy = (vars->map->height - 1) * 0.5;

    // --- translate so center is origin ---
    double x0 = pt.x - cx;
    double y0 = pt.y - cy;
    double z0 = pt.z;

    // --- tilt around X-axis (W/S) ---
    double cX = cos(vars->rot_x_angle);
    double sX = sin(vars->rot_x_angle);
    double y1 = y0 * cX - z0 * sX;
    double z1 = y0 * sX + z0 * cX;

    // --- rotate around Z-axis (Q/E) ---
    double cZ = cos(vars->rot_angle);
    double sZ = sin(vars->rot_angle);
    double x2 = x0 * cZ - y1 * sZ;
    double y2 = x0 * sZ + y1 * cZ;

    // --- apply zoom & vertical scale ---
    x2 *= vars->zoom;
    y2 *= vars->zoom;
    z1 *= Z_SCALE * vars->zoom;

    // --- isometric projection + screen offset ---
    t_point iso = project_iso((t_point){ (int)x2, (int)y2, (int)z1 });
    iso.x += vars->offset_x;
    iso.y += vars->offset_y;
    return iso;
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
