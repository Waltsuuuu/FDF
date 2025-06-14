/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:00 by wheino            #+#    #+#             */
/*   Updated: 2025/05/15 18:16:34 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memcpy(void *dest, const void *src, size_t n)
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

size_t	gnl_strlen(const char *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = gnl_strlen((char *)s1) + gnl_strlen((char *)s2) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*gnl_strdup(const char *s)
{
	char	*new_str;
	size_t	len;

	if (!s)
		return (NULL);
	len = gnl_strlen((char *)s) + 1;
	new_str = malloc(len * sizeof(char));
	if (!new_str)
		return (NULL);
	gnl_memcpy(new_str, s, len);
	return (new_str);
}
