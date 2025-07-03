/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:13:22 by wheino            #+#    #+#             */
/*   Updated: 2025/07/03 14:51:15 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static unsigned int	word_count(char *s, char c)
{
	unsigned int	i;
	unsigned int	wc;
	char			*newline;

	i = 0;
	wc = 0;
	newline = ft_strchr(s, '\n');
	if (newline)
		*newline = '\0';
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			wc++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (wc);
}

static char	*fill_word(char *s, char c)
{
	int			i;
	size_t		start;
	size_t		end;
	char		*word;

	i = 0;
	while (s[i] == c)
		i++;
	start = i;
	while (s[i] != c && s[i])
		i++;
	end = i;
	word = malloc((end - start) * (sizeof(char)) + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char				**arr;
	unsigned int		i;
	char				*temp_s;

	temp_s = (char *)s;
	arr = malloc((word_count((char *)s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < word_count((char *)s, c))
	{
		while (*temp_s == c)
			temp_s++;
		arr[i] = fill_word(temp_s, c);
		if (!arr[i])
		{
			free_arr(arr, i);
			return (NULL);
		}
		temp_s = temp_s + ft_strlen(arr[i]) + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
