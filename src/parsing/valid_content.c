/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:02:02 by romorale          #+#    #+#             */
/*   Updated: 2026/05/18 19:44:30 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_map_chars(char **map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!map)
		return (0);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'N'
				&& map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W'
				&& map[j][i] != 'P' && map[j][i] != 'K' && map[j][i] != 32)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	valid_single_player(char **map)
{
	int	j;
	int	i;
	int	player;

	j = 0;
	i = 0;
	player = 0;
	if (!map)
		return (0);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
				player++;
			i++;
		}
		j++;
	}
	if (player != 1)
		return (0);
	else
		return (1);
}

int	empty_line(char *line)
{
	int	i;
	int	not_space;

	i = 0;
	not_space = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != 32 && (!(line[i] >= 9 && line[i] <= 13)))
			not_space++;
		i++;
	}
	if (not_space != 0)
		return (0);
	return (1);
}

int	no_empty_lines(char **map)
{
	int	j;

	j = 0;
	if (!map)
		return (0);
	while (map[j])
	{
		if (empty_line(map[j]))
		{
			return (0);
		}
		j++;
	}
	return (1);
}

int	valid_content(t_dpar *game)
{
	if (!game->map_s->map)
		return (0);
	else
	{
		if (!no_empty_lines(game->map_s->map)
			|| !valid_single_player(game->map_s->map)
			|| !valid_map_chars(game->map_s->map))
		{
			printf(B_R "Error\n " RED);
			printf(" Missing or invalid chars in the map!\n" RES);
			return (0);
		}
	}
	return (1);
}
