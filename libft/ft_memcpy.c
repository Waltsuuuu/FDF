/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:47:27 by wheino            #+#    #+#             */
/*   Updated: 2025/05/27 15:00:17 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from the memory area src to the memory area dest.
 *        The memory areas must not overlap.
 * @param dest: Pointer to the destination memory area.
 * @param src: Pointer to the source memory area.
 * @param n: Number of bytes to copy.
 * @return Pointer to the destination memory area dest.
 * 	   	   If n is zero, the function returns dest.
 */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_str;
	const unsigned char	*src_str;
	size_t				i;

	if (!dest || !src)
		return (NULL);
	dest_str = (unsigned char *)dest;
	src_str = (const unsigned char *)src;
	i = 0;
	while (n--)
	{
		dest_str[i] = src_str[i];
		i++;
	}
	return (dest_str);
}
