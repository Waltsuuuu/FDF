/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_row_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:37:05 by wheino            #+#    #+#             */
/*   Updated: 2025/06/25 18:52:32 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Ensure all rows have the same width
int	check_or_set_width(int *map_width, int line_width)
{
	if (*map_width == 0)
		*map_width = line_width;
	else if (*map_width != line_width)
		return (1);
	return (0);
}

// Allocate one row of t_point
t_point	*alloc_row(int line_width)
{
	t_point	*row;

	row = malloc(sizeof * row * line_width);
	if (!row)
		return (NULL);
	return (row);
}

// Fill one row from the split values
void	fill_row(t_point *row, char **values, int current_height)
{
	int	x;

	x = 0;
	while (values[x])
	{
		row[x].x = x;
		row[x].y = current_height;
		row[x].z = ft_atoi(values[x]);
		x++;
	}
}

// Parse one line into a row and append to rows_list
int	parse_and_add_row(t_list **rows_list,
	char *line, int current_height, int *map_width)
{
	char	**values;
	int		line_width;
	t_point	*row;

	values = ft_split(line, ' ');
	line_width = word_count(values);
	if (check_or_set_width(map_width, line_width))
	{
		free_line_and_values(line, values);
		return (-1);
	}
	row = alloc_row(line_width);
	if (!row)
	{
		free_line_and_values(line, values);
		return (-1);
	}
	fill_row(row, values, current_height);
	ft_lstadd_back(rows_list, ft_lstnew(row));
	free_line_and_values(line, values);
	return (0);
}
