/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:25 by romorale          #+#    #+#             */
/*   Updated: 2026/04/21 17:52:32 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_old_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

char	*map_dup_line(const char *s, int max_len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(max_len * sizeof(char) + 1);
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	if (i < max_len)
	{
		while (i < max_len)
		{
			dest[i] = ' ';
			i++;
		}
	}
	dest[max_len] = '\0';
	return (dest);
}

char	**recopy_map(char **og_map, int max_len, int row_len)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = malloc((sizeof(char *) *(row_len + 1)) + 1);
	if (!new_map)
		return (NULL);
	while (og_map[i] && i < row_len)
	{
		new_map[i] = map_dup_line(og_map[i], max_len);
		i++;
	}
	new_map[row_len] = 0;
	free_old_map(og_map);
	return (new_map);
}

void	square_map(t_dpar *g)
{
	g->map_s->map = recopy_map(g->map_s->map, g->map_s->cols, g->map_s->rows);
}
