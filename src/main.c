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
// tester main
int main(void)
{

		void	*mlx;
	void	*window;

	// Initialize MiniLibX
	mlx = mlx_init();
	if (!mlx)
		return (1);

	// Create a new window: width, height, title
	window = mlx_new_window(mlx, 800, 600, "MiniLibX Test");
	if (!window)
		return (1);

	// Keep the window open until manually closed
	mlx_loop(mlx);
	return (0);
	t_map *map;
	int fd = open("test_maps/42.fdf", O_RDONLY);

	map = parse_map(fd);
	close(fd);
	if (!map)
	{
		printf("Failed to parse map\n");
		return (1);
	}
	printf("Map parsed successfully!\n");
	printf("Width: %d, Height: %d\n", map->width, map->height);

	// print out the map points (only z-values)
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			printf("%3d ", map->points[y][x].z);
		}
		printf("\n");
	}

	// cleanup
	for (int i = 0; i < map->height; i++)
		free(map->points[i]);
	free(map->points);
	free(map);

	return (0);
}