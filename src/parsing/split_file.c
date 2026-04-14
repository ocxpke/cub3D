/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:55:20 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 16:01:40 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ctword(const char *s, char c)
{
	unsigned int	count;
	int				i;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	if (!c)
		return (*s != '\0');
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	count++;
	return (count);
}

static char	*saveword(const char *s, char c)
{
	char	*str;
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[n] && s[n] != c)
		n++;
	if (s[0] == c)
		n += 1;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[n] = '\0';
	return (str);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**split_file(char *s, char c)
{
	char	**array;
	int		i;

	i = 0;
	array = (char **)malloc(sizeof(char *) * (ctword(s, c) + 1));
	if (!array || !s)
		return (NULL);
	while (*s)
	{
		if (*s)
		{
			array[i] = saveword(s, c);
			if (array[i] == NULL)
				return (free_array(array));
			i++;
			while (*s && *s != c)
				s++;
			if (*s == c)
				s += 1;
		}
	}
	array[i] = NULL;
	return (array);
}
