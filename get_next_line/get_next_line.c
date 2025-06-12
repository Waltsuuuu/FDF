/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/06/12 13:43:07 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strldup(const char *s, size_t len)
{
	char	*new_str;

	new_str = malloc(len * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	gnl_memcpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}

char	*read_operation(int fd, char *buf, char *stash)
{
	int		bytes_read;
	char	*temp_stash;

	if (gnl_strchr(stash, '\n'))
		return (stash);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			buf[0] = '\0';
		else
			buf[bytes_read] = '\0';
		temp_stash = gnl_strjoin(stash, buf);
		free (stash);
		stash = temp_stash;
		if (gnl_strchr(stash, '\n') != NULL || bytes_read <= 0)
			break ;
	}
	return (stash);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (gnl_strlen((char *)src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (gnl_strlen((char *)src));
}

char	*extract_line(char *stash, char *leftover)
{
	char	*line;
	char	*newline_ptr;
	int		newline_index;

	newline_ptr = gnl_strchr(stash, '\n');
	if (newline_ptr)
	{
		newline_index = 0;
		while (stash[newline_index] != '\n')
			newline_index++;
		line = gnl_strldup(stash, newline_index + 1);
		if (!line)
			return (NULL);
		gnl_strlcpy(leftover, newline_ptr + 1, BUFFER_SIZE + 1);
	}
	else
	{
		line = gnl_strdup(stash);
		if (!line)
			return (NULL);
		leftover[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*stash;
	char		*line;
	static char	leftover[BUFFER_SIZE + 1];

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	stash = gnl_strdup(leftover);
	if (!stash)
	{
		free (buf);
		return (NULL);
	}
	stash = read_operation(fd, buf, stash);
	if (stash == NULL || *stash == '\0')
	{
		free (buf);
		free (stash);
		return (NULL);
	}
	line = extract_line(stash, leftover);
	free (buf);
	free (stash);
	return (line);
}
