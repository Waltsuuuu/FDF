#include "fdf.h"

int main(void)
{
	t_vars vars;

	// Init mlx
	if ((init_mlx(&vars, 1200, 800, "FDF") == 0))
		return (0);

	// Parse map
	int fd = open("test_maps/42.fdf", O_RDONLY);
	vars.map = parse_map(fd);
	if (!vars.map)
	{
		printf("map parsing failed\n");
		return (0);
	}
	close(fd);

	// Offset calculation for isometric projection
	calculate_offset(&vars);

	// Draw the grid / wireframe
	draw_grid(&vars);

	// Display the image to the window
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

	// Keep the mlx window running
    mlx_loop(vars.mlx);

	// Cleanup
	// for (int i = 0; i < vars.map->height; i++)
	// 	free(vars.map->points[i]);
	// free(vars.map->points);
	// free(vars.map);

	return (0);
}
