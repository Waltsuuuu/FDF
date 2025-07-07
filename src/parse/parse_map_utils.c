/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:34:36 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 21:06:30 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	word_count(char **values)
{
	int	i;

	i = 0;
	while (values[i] != NULL)
		i++;
	return (i);
}

void	keep_content_free_nodes(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_nodes_and_content(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	free_row_line_values(t_point *row, char *line, char **values)
{
	int	i;

	if (row != NULL)
		free(row);
	if (line != NULL)
		free(line);
	if (values != NULL)
	{
		i = 0;
		while (values[i] != NULL)
			free(values[i++]);
		free(values);
	}
	return (ERROR);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	if (map->points != NULL)
	{
		while (i < map->height)
		{
			free(map->points[i]);
			i++;
		}
		free(map->points);
	}
	free(map);
}
