/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:03 by wheino            #+#    #+#             */
/*   Updated: 2025/06/12 13:47:59 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>

size_t	gnl_strlen(const char *src);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
void	*gnl_memcpy(void *dest, const void *src, size_t n);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s);
char	*gnl_strldup(const char *s, size_t len);
char	*read_operation(int fd, char *buf, char *stash);
char	*extract_line(char *stash, char *leftover);
char	*get_next_line(int fd);

#endif