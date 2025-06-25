/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:34:36 by wheino            #+#    #+#             */
/*   Updated: 2025/06/25 18:45:33 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Count the number of extracted values (width of map)
int word_count(char **values)
{
	int i;

	i = 0;
	while(values[i] != NULL)
		i++;
	return (i);
}
// Free nodes, but not the content variable (ft_lstclear variation)
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

// Free the GNL line and its split tokens
void free_line_and_values(char *line, char **values)
{
    int i;

    free(line);
    i = 0;
    while (values[i])
    {
        free(values[i]);
        i++;
    }
    free(values);
}
