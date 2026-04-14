/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:25 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 16:03:59 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_maplen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**get_the_map(char **found_map, int start)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = malloc((sizeof(char *) *(get_maplen(found_map))) + 1);
	if (!new_map)
		return (NULL);
	while (found_map[start])
	{
		new_map[i] = ft_strdup(found_map[start]);
		i++;
		start++;
	}
	new_map[i] = 0;
	return (new_map);
}

int	map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || (c == 32 || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}

int	find_map(t_dpar *g)
{
	int	i;
	int	j;
	int	map_line;

	i = 0;
	j = 0;
	map_line = 0;
	while (g->file_cont && !map_line)
	{
		i = 0;
		while (map_char(g->file_cont[j][i]))
		{
			if ((g->file_cont[j][i] == '1' || g->file_cont[j][i] == '0')
					&& !map_line)
				map_line = j;
			i++;
		}
		j++;
	}
	if (map_line)
	{
		g->map_s->map = get_the_map(g->file_cont, map_line);
		return (1);
	}
	return (0);
}
