/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inner_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:02:02 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 17:08:39 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_exposed_corner(char **map, int j, int i)
{
	if (map[j])
	{
		if (map[j][i])
		{
			if (j - 1 < 0)
				return (0);
			if (!val_inside_c(map[j - 1][i - 1])
				&& map[j - 1][i - 1] != '1')
				return (0);
			if (!val_inside_c(map[j - 1][i + 1])
				&& map[j - 1][i + 1] != '1')
				return (0);
			if (!map[j + 1])
				return (0);
			if (!val_inside_c(map[j + 1][i - 1])
				&& map[j + 1][i - 1] != '1')
				return (0);
			if (!val_inside_c(map[j + 1][i + 1])
				&& map[j + 1][i + 1] != '1')
				return (0);
		}
	}
	return (1);
}

int	check_exposed_char(char **map, int j, int i)
{
	if (map[j])
	{
		if (map[j][i])
		{
			if (!val_inside_c(map[j][i - 1]) && map[j][i - 1] != '1')
				return (0);
			if (!val_inside_c(map[j][i + 1]) && map[j][i + 1] != '1')
				return (0);
			if (j - 1 < 0)
				return (0);
			if (!val_inside_c(map[j - 1][i]) && map[j - 1][i] != '1')
				return (0);
			if (!map[j + 1])
				return (0);
			if (!val_inside_c(map[j + 1][i]) && map[j + 1][i] != '1')
				return (0);
		}
	}
	return (1);
}

int	check_inner_chars(t_data *game)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!game->map_s->map)
		return (0);
	while (game->map_s->map[j])
	{
		i = 0;
		while (game->map_s->map[j][i])
		{
			if (val_inside_c(game->map_s->map[j][i]))
				if (!check_exposed_char(game->map_s->map, j, i)
					|| !check_exposed_corner(game->map_s->map, j, i))
					return (0);
			i++;
		}
		j++;
	}
	return (1);
}
