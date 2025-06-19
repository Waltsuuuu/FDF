#include "fdf.h"

// helper to count the number of extracted values (width of map)
int word_count(char **values)
{
	int i;

	i = 0;
	while(values[i] != NULL)
		i++;
	return (i);
}
// like ft_lstclear but does not clear the content variable of the node
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
		printf("Line %d: width = %d\n", current_height + 1, line_width);
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

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
    	return;
	dst = vars->img_data + (y * vars->line_len + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}
// Initialize mlx and prepare a window.
int	init_mlx(t_vars *vars, int width, int height, char *title)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		printf("mlx init failed\n");
		return (0);
	}
	vars->win = mlx_new_window(vars->mlx, width, height, title);
	if (!vars->win)
	{
		printf("window init failed\n");
		return (0);
	}
	vars->img = mlx_new_image(vars->mlx, 1200, 800);
	if (!vars->img)
	{
		printf("img init failed\n");
		return (0);
	}
	vars->img_data = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len, &vars->endian); // Pointer to the first byte of the image pixel data
	if (!vars->img_data)
	{
		printf("img_data failed\n");
		return (0);
	}
	return (1);
}

void	init_line(t_line *line, int x0, int y0, int x1, int y1)
{
	line->dx = abs(x1 - x0);
	line->dy = -abs(y1 - y0);
	if (x0 < x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (y0 < y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
	t_line line;

	init_line(&line, x0, y0, x1, y1);
	while (1)
	{
		put_pixel(vars, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			y0 += line.sy;
		}
	}
}

t_point	project_2d(t_point p, t_vars *vars)
{
	t_point projected;

	projected.x = p.x * TILE_SIZE + vars->offset_x;
	projected.y = p.y * TILE_SIZE + vars->offset_y;
	projected.z = p.z;
	return (projected);
}

t_point project_iso(t_point p)
{
	t_point res;
	double angle = 0.523599; // ~30 degrees

	double x = p.x * TILE_SIZE;
	double y = p.y * TILE_SIZE;
	double z = p.z * Z_SCALE;


	res.x = (x - y) * cos(angle);
	res.y = (x + y) * sin(angle) - z;
	res.z = p.z;
	return res;
}

void	draw_grid_2d(t_vars *vars)
{
	int		x, y;
	t_point	a, b;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			a = project_iso(vars->map->points[y][x]);
			a.x += vars->offset_x;
			a.y += vars->offset_y;

			if (x < vars->map->width - 1)
			{
				b = project_iso(vars->map->points[y][x + 1]);
				b.x += vars->offset_x;
				b.y += vars->offset_y;
				draw_line(vars, a.x, a.y, b.x, b.y, 0xFFFFFF);
			}
			if (y < vars->map->height - 1)
			{
				b = project_iso(vars->map->points[y + 1][x]);
				b.x += vars->offset_x;
				b.y += vars->offset_y;
				draw_line(vars, a.x, a.y, b.x, b.y, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
}

void calculate_offset(t_vars *vars)
{
    int x, y;
    double min_x = 1e9, max_x = -1e9;
    double min_y = 1e9, max_y = -1e9;
    t_point p;

    for (y = 0; y < vars->map->height; y++)
    {
        for (x = 0; x < vars->map->width; x++)
        {
            p = project_iso(vars->map->points[y][x]);
            if (p.x < min_x) min_x = p.x;
            if (p.x > max_x) max_x = p.x;
            if (p.y < min_y) min_y = p.y;
            if (p.y > max_y) max_y = p.y;
        }
    }

    vars->offset_x = (WIN_WIDTH - (max_x - min_x)) / 2 - min_x;
    vars->offset_y = (WIN_HEIGHT - (max_y - min_y)) / 2 - min_y;
}

int main(void)
{
	t_vars vars;
	int fd = open("test_maps/42.fdf", O_RDONLY);

	if ((init_mlx(&vars, 1200, 800, "FDF") == 0))
		return (0);

	vars.map = parse_map(fd);
	if (!vars.map)
	{
		printf("map parsing failed\n");
		return (0);
	}
	printf("Parsed map: width=%d, height=%d\n", vars.map->width, vars.map->height);
	close(fd);

	//offset calculation for iso proj
	calculate_offset(&vars);

	// draw grid
	draw_grid_2d(&vars);

	// Display the image in the window
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

    mlx_loop(vars.mlx);

	// cleanup
	// for (int i = 0; i < vars.map->height; i++)
	// 	free(vars.map->points[i]);
	// free(vars.map->points);
	// free(vars.map);

	return (0);
}