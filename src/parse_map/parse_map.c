/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:26 by wheino            #+#    #+#             */
/*   Updated: 2025/06/25 18:46:46 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *parse_map(int fd)
{
    t_map  *map;
    t_list *rows_list;
    int     current_height;

    map = init_map();
    if (!map)
        return (NULL);

    rows_list = read_all_rows(fd, &map->width, &current_height);
    if (!rows_list)
    {
        free(map);
        return (NULL);
    }

    map->height = current_height;
    map->points = build_points_array(rows_list, current_height);
    free_nodes_keep_content(&rows_list);
    return (map);
}

// Create and initialize the map
t_map *init_map(void)
{
	t_map *map = malloc(sizeof(t_map));
	if (!map)
		return (NULL); 
	map->width = 0;
	map->height = 0;
	return (map);
}

// Read all lines, build up the linked list of rows
t_list *read_all_rows(int fd, int *map_width, int *current_height)
{
    t_list *rows_list;
	char   *line;
    int     h;
    int     res;

    rows_list = NULL;
    h = 0;
    while ((line = get_next_line(fd)))
    {
        res = parse_and_add_row(&rows_list, line, h, map_width);
        if (res < 0)
        {
            free_nodes_keep_content(&rows_list);
            return (NULL);
        }
        h++;
    }
    *current_height = h;
    return (rows_list);
}

// Turn the linked list into the final array of point-rows
t_point **build_points_array(t_list *rows_list, int current_height)
{
    t_point **points;
    t_list   *node;
    int       i;

    points = malloc(sizeof *points * current_height);
    if (!points)
    {
        free_nodes_keep_content(&rows_list);
        return (NULL);
    }
    node = rows_list;
    i = 0;
    while (node)
    {
        points[i] = node->content;
        i++;
        node = node->next;
    }
    return (points);
}