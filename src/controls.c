// controls.c
// Handles zooming, rotation, tilting, and mouse scroll for fdf project
// The model's center stays fixed at the screen center

#include "fdf.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ZOOM_FACTOR 1.1

// Clears the image buffer
static void clear_image(t_vars *vars) {
    memset(vars->img_data, 0, vars->line_len * WIN_HEIGHT);
}

// Always recenter the model's projected center to the window center
static void recenter(t_vars *vars) {
    double b[4];
    get_iso_bounds(vars, b);
    double cx = (b[0] + b[1]) * 0.5;
    double cy = (b[2] + b[3]) * 0.5;
    vars->offset_x = (WIN_WIDTH  * 0.5) - cx;
    vars->offset_y = (WIN_HEIGHT * 0.5) - cy;
}

// Key press handler: zoom, rotate, tilt, quit
int handle_key(int keycode, void *param) {
    t_vars *vars = (t_vars *)param;

    if (keycode == KEY_ESC)
        exit(0);

    // Zoom in/out
    else if (keycode == 61 || keycode == 24)        // '=' key
        vars->zoom *= ZOOM_FACTOR;
    else if (keycode == 45 || keycode == 27)        // '-' key
        vars->zoom /= ZOOM_FACTOR;

    // Rotate around Z-axis (Q/E)
    else if (keycode == KEY_ROT_CCW)
        vars->rot_angle -= ROT_STEP;
    else if (keycode == KEY_ROT_CW)
        vars->rot_angle += ROT_STEP;

    // Tilt around X-axis (W/S)
    else if (keycode == KEY_TILT_UP)
        vars->rot_x_angle -= TILT_STEP;
    else if (keycode == KEY_TILT_DOWN)
        vars->rot_x_angle += TILT_STEP;

    else
        return 0;

    // Normalize rotation angle to [0, 2π)
    if (vars->rot_angle < 0)
        vars->rot_angle += M_PI * 2;
    else if (vars->rot_angle >= M_PI * 2)
        vars->rot_angle -= M_PI * 2;

    // Normalize tilt angle to [0, 2π) for continuous rotation
    if (vars->rot_x_angle < 0)
        vars->rot_x_angle += M_PI * 2;
    else if (vars->rot_x_angle >= M_PI * 2)
        vars->rot_x_angle -= M_PI * 2;

    // Recenter and redraw on any transformation
    recenter(vars);
    clear_image(vars);
    draw_grid(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
    return 0;
}

// Mouse scroll: zoom
int handle_mouse(int button, int x, int y, void *param) {
    t_vars *vars = (t_vars *)param;
    (void)x; (void)y;

    if (button == 4)
        vars->zoom *= ZOOM_FACTOR;
    else if (button == 5)
        vars->zoom /= ZOOM_FACTOR;
    else
        return 0;

    recenter(vars);
    clear_image(vars);
    draw_grid(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
    return 0;
}
