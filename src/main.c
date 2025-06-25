#include "fdf.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if(argc != 2)
		return 0;

	// Init mlx
	if ((init_mlx(&vars, WIN_WIDTH, WIN_HEIGHT, "FDF") == 0))
		return (0);

	// Parse map
	int fd = open(argv[1], O_RDONLY);
	vars.map = parse_map(fd);
	if (!vars.map)
	{
		printf("map parsing failed\n");
		return (0);
	}
	close(fd);

	// computes zoom and centering
	scale_and_center(&vars);
	vars.zoom = 10.0;


	// Draw the grid / wireframe
	draw_grid(&vars);

	// Display the image to the window
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

	vars.pan_x       = 0;
	vars.pan_y       = 0;
	vars.base_off_x  = 0;
	vars.base_off_y  = 0;
    vars.rot_angle   = 0.0;
    vars.rot_x_angle = 0.0;

    // Full keypresses (so arrow keys work on macOS & X11):
    mlx_hook(vars.win, 2, 1L << 0, handle_key,   &vars);
    // Mouse scroll events:
    mlx_mouse_hook(vars.win, handle_mouse, &vars);
	
	// Keep the mlx window running
    mlx_loop(vars.mlx);

	// Cleanup
	// for (int i = 0; i < vars.map->height; i++)
	// 	free(vars.map->points[i]);
	// free(vars.map->points);
	// free(vars.map);

	return (0);
}
