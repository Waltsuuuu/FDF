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
