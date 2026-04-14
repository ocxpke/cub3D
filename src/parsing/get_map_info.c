/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:39 by romorale          #+#    #+#             */
/*   Updated: 2026/04/08 15:47:34 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_rows(char **map)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (map[j])
		j++;
	len = j;
	return (len);
}

int	get_cols(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
			i++;
		if (i > max)
			max = i;
		j++;
	}
	return (max);
}

char	get_orientation(char **map)
{
	int		i;
	int		j;
	char	player_char;

	i = 0;
	j = 0;
	player_char = '\0';
	while (map[j])
	{
		i = 0;
		while (map[j][i] && !player_char)
		{
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
				player_char = map[j][i];
			i++;
		}
		j++;
	}
	return (player_char);
}

int	get_player_pos_row(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
				return (j);
			i++;
		}
		j++;
	}
	return (-1);
}

int	get_player_pos_col(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
				return (i);
			i++;
		}
		j++;
	}
	return (-1);
}
