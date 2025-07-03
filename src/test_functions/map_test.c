#include "fdf.h"

void print_map(t_map *map)
{
    if (!map)
    {
        ft_printf("Error: map is NULL.\n");
        return;
    }

    ft_printf("Map dimensions: width = %d, height = %d\n", map->width, map->height);
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            ft_printf("(%d,%d,%d) ", 
                map->points[y][x].x,
                map->points[y][x].y,
                map->points[y][x].z);
        }
        ft_printf("\n");
    }
}