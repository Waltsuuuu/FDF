/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:26 by wheino            #+#    #+#             */
/*   Updated: 2025/07/14 22:00:38 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*open_and_parse_map(const char *path)
{
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Invalid fd");
		return (NULL);
	}
	map = parse_map(fd);
	if (!map)
	{
		ft_printf("ERROR: Map parsing error.\n");
		return (NULL);
	}
	if (map->height <= 1)
	{
		ft_printf("ERROR: Map needs to have more than 1 row!\n");
		free_map(map);
		return (NULL);
	}
	close(fd);
	return (map);
}

t_map	*parse_map(int fd)
{
	t_map	*map;
	t_list	*rows_list;
	int		current_height;

	map = init_map_variables();
	if (!map)
		return (NULL);
	rows_list = read_map_rows(fd, &map->width, &current_height);
	if (!rows_list)
	{
		free_map(map);
		return (NULL);
	}
	map->height = current_height;
	map->points = convert_list_to_2d_points_array(rows_list, current_height);
	if (!map->points)
	{
		free_nodes_and_content(&rows_list);
		free_map(map);
		return (NULL);
	}
	keep_content_free_nodes(&rows_list);
	return (map);
}

t_map	*init_map_variables(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 0;
	map->height = 0;
	map->points = NULL;
	return (map);
}

t_list	*read_map_rows(int fd, int *map_width, int *current_height)
{
	t_list	*rows_list;
	char	*line;
	int		y_index;
	int		error_check;

	rows_list = NULL;
	y_index = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		error_check = parse_and_add_row(&rows_list, line, y_index, map_width);
		if (error_check == ERROR)
		{
			free_nodes_and_content(&rows_list);
			return (NULL);
		}
		y_index++;
		line = get_next_line(fd);
	}
	*current_height = y_index;
	return (rows_list);
}

t_point	**convert_list_to_2d_points_array(t_list *rows_list, int current_height)
{
	t_point	**points;
	t_list	*node;
	int		i;

	points = malloc((sizeof (*points)) * current_height);
	if (!points)
		return (NULL);
	node = rows_list;
	i = 0;
	while (node != NULL)
	{
		points[i] = node->content;
		i++;
		node = node->next;
	}
	return (points);
}
