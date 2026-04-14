/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:02:02 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 17:06:09 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_inside(int inside)
{
	if (inside == 0)
		return (1);
	return (0);
}

int	val_inside_c(char c)
{
	if (c != '0' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	is_enclosed(char **map)
{
	int	j;
	int	i;
	int	inside;

	j = -1;
	i = -1;
	inside = 0;
	while (map[++j])
	{
		i = 0;
		while (map[j][++i])
		{
			if (i - 1 < 0)
				break ;
			if (val_inside_c(map[j][i]) && map[j][i - 1] == '1' && !inside)
				inside = 1;
			else if (val_inside_c(map[j][i]) && !inside)
				return (0);
			else if (map[j][i] == '1' && val_inside_c(map[j][i - 1]) && inside)
				inside = 0;
		}
		if (inside != 0)
			return (0);
	}
	return (is_inside(inside));
}

int	valid_structure(t_dpar *game)
{
	if (!game->map_s->map)
		return (0);
	else
	{
		if (!is_enclosed(game->map_s->map) || !check_inner_chars(game))
		{
			printf(B_R"Error:"RED" The map structure is invalid!\n"RES);
			return (0);
		}
	}
	return (1);
}
