/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:43:46 by wheino            #+#    #+#             */
/*   Updated: 2025/05/27 15:01:38 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * * @brief Computes the length of the string src, excluding the null terminator.
 * * @param src: The string whose length is to be computed.
 * * @return The length of the string src.
 * *         If src is NULL, the function returns 0.
 */

size_t	ft_strlen(const char *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}
