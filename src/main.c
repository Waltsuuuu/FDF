#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h> //Printf - testing
#include "fcntl.h" //Read

// helper to count the number of extracted values (width of map)
int word_count(char **values)
{
	int i;

	i = 0;
	while(values[i] != NULL)
		i++;
	return (i);
}
// ft_lstclear but does not clear the content variable of the node
void free_nodes_keep_content(t_list **lst)
{
    t_list *tmp;

    if (!lst)
        return;
    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}
// parses the map ofc
t_map *parse_map(int fd)
{
	t_point	*row; // to store the extracted row values
	t_map	*map; // to store the map height, width and t_points (x, y ,z)
	t_list	*rows_list; // linked list to temporarily hold rows
	t_list	*node; // iterator for the linked list nodes
    char	*line; // line returned by gnl
    char	**values; // extracted values from the line (split output)
    int		line_width; // number of values in the current line
	int		x; // x-axis index 
	int		current_height; // y-axis index
	int		i; // iterator
	
	rows_list = NULL;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL); 
	// Add cleanup here
	map->width = 0;
	map->height = 0;
	current_height = 0;
	while ((line = get_next_line(fd)) != NULL) // #1
	{
		values = ft_split(line, ' '); // #2 Split the values
		line_width = word_count(values); // #3 Calculate the map width
		if (map->width == 0) // #4 Set the map width
			map->width = line_width;
		else if (map->width != line_width)
			return (NULL); //Throw error if rows are not equal length 
			// Add cleanup here
		row = malloc(sizeof(t_point) * line_width); // #5
		if (!row)
			return (NULL);
		//Add cleanup here
		x = 0;
		while (x < line_width) // #6 fill the row
		{
			row[x].x = x;
			row[x].y = current_height;
			row[x].z = ft_atoi(values[x]);
			x++;
		}
		ft_lstadd_back(&rows_list, ft_lstnew(row)); // #7 Store the row in linked list
		current_height++; // #8 increase height
		free(line); // #10 free line and the split values. 
		x = 0;
		while (values[x])
			free(values[x++]);
		free(values);
	}
	map->height = ft_lstsize(rows_list); // #10 set the map height to the number of rows extracted
	map->points = malloc(sizeof(t_point *) * map->height); // #11 allocate mem for map points
	if (!map->points)
		return (NULL);
	//Add cleanup
	node = rows_list;
	i = 0;
	while (node)
	{
		map->points[i++] = (t_point *)node->content;
		node = node->next;
	}
	free_nodes_keep_content(&rows_list);
	return (map);
}
// Places pixel at x, y, with a color.
void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char *dst;

	dst = vars->img_data + (y * vars->line_len + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}

int main(void)
{
	t_vars vars; //Variables for mlx environment

	// Initialize mlx and window
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		printf("mlx init failed\n");
		return (0);
	}
	vars.win = mlx_new_window(vars.mlx, 800, 600, "FDF");
	if (!vars.win)
	{
		printf("window init failed\n");
		return (0);
	}

	// Parse the map
	int fd = open("test_maps/42.fdf", O_RDONLY);
	vars.map = parse_map(fd);
	if (!vars.map)
	{
		printf("map parsing failed\n");
		return (0);
	}
	close(fd);

	// Create image
	vars.img = mlx_new_image(vars.mlx, 800, 600);
	if (!vars.img)
	{
		printf("img init failed\n");
		return (0);
	}
	vars.img_data = mlx_get_data_addr(vars.img, &vars.bpp, &vars.line_len, &vars.endian); // Pointer to the first byte of the image pixel data
	if (!vars.img_data)
	{
		printf("img_data failed\n");
		return (0);
	}
	// Draw a single pixel in the image
	printf("Before pixel\n");
	put_pixel(&vars, 100, 100, 0x00FF0000); // Red pixel at (100, 100)
	printf("After pixel\n");

	// Display the image in the window
	printf("Before placing image\n");
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	printf("After placing image\n");

    mlx_loop(vars.mlx);

	// cleanup
	// for (int i = 0; i < vars.map->height; i++)
	// 	free(vars.map->points[i]);
	// free(vars.map->points);
	// free(vars.map);

	return (0);
}