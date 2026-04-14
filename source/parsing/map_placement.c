/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_placement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:47:05 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 17:32:29 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	valid_element_chars(char *str)
{
	if ((str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		|| (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		|| (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		|| (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		|| (str[0] == 'F' && str[1] == ' ')
		|| (str[0] == 'C' && str[1] == ' '))
		return (1);
	return (0);
}

int	last_elements_line(char **line)
{
	int	j;
	int	elements;

	j = 0;
	elements = 0;
	if (!line)
		return (0);
	while (line[j] && elements != 6)
	{
		if (valid_element_chars(line[j]))
			elements++;
		j++;
	}
	j--;
	if (elements == 6)
		return (j);
	else
		return (0);
}

int	map_chars(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	first_map_line(char **line)
{
	int	j;
	int	i;
	int	map_line;
	int	in_map;

	j = -1;
	i = 0;
	map_line = 0;
	in_map = 0;
	if (!line)
		return (0);
	while (line[++j] && !in_map)
	{
		i = 0;
		while (line[j][i] && !in_map && map_chars(line[j]))
		{
			if (line[j][i] == '1' && !in_map)
				in_map++;
			i++;
		}
		if (in_map)
			map_line = j;
	}
	map_line++;
	return (map_line);
}

int	map_placement(t_data *game)
{
	int	map_line;
	int	not_map_line;

	map_line = first_map_line(game->file_cont);
	not_map_line = last_elements_line(game->file_cont);
	if (!game->file_cont)
		return (0);
	if (map_line < not_map_line)
		return (0);
	else
		return (1);
}
