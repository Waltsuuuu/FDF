#include "fdf.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if(argc != 2)
		return 0;
	int fd = open(argv[1], O_RDONLY);
	vars.map = parse_map(fd);
	if (!vars.map)
	{	
		ft_printf("Error parsing map\n");
		return (0);
	}
	if ((init_mlx(&vars, WIN_WIDTH, WIN_HEIGHT, "FDF") == 0))
			return (0);
	print_map(vars.map);
	close(fd);
    //mlx_loop(vars.mlx);
	free_and_destroy(&vars);
	return (0);
}

void	free_and_destroy(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx); 
	free_map(vars->map);
}