#include "fdf.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if(argc != 2)
		return 0;
	ft_bzero(&vars, sizeof vars);
	int fd = open(argv[1], O_RDONLY);
	vars.map = parse_map(fd);
	if (!vars.map)
	{	
		ft_printf("Error parsing map\n");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	if ((init_mlx(&vars, WIN_WIDTH, WIN_HEIGHT, "FDF") == ERROR))
		return (free_and_destroy(&vars));
	print_map(vars.map); // Testing only
    //mlx_loop(vars.mlx);
	free_and_destroy(&vars);
	return (EXIT_SUCCESS);
}
