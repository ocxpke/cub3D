/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_anything_else.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:25:43 by romorale          #+#    #+#             */
/*   Updated: 2026/04/08 18:45:58 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	map_chars_2(char c)
{
	if (c == '1' || c == '0' || (c == 32 || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}

int	element_chars_2(char *str)
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

int	check_for_anything_else(t_data *game)
{
	int	j;

	j = 0;
	if (!game->file_cont)
		return (0);
	if (game->file_cont)
	{
		while (game->file_cont[j])
		{
			if (!element_chars_2(game->file_cont[j])
				&& !map_chars_2(game->file_cont[j][0]))
			{
				return (0);
			}
			j++;
		}
	}
	return (1);
}
