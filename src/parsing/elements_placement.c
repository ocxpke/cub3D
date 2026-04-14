/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_placement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:47:05 by romorale          #+#    #+#             */
/*   Updated: 2026/04/08 19:02:48 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	element_order_number(char *str)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		return (1);
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		return (2);
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		return (3);
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		return (4);
	else if (str[0] == 'F' && str[1] == ' ')
		return (5);
	else if (str[0] == 'C' && str[1] == ' ')
		return (6);
	else
		return (0);
}

int	element_chars(char *str)
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

int	element_line_order(char **line, int j)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (element_chars(line[j]))
				return (element_order_number(line[j]));
			i++;
		}
		j++;
	}
	return (0);
}

int	check_elements_placement(t_dpar *game)
{
	int	prev_el_order;
	int	next_el_order;
	int	j;

	prev_el_order = 0;
	next_el_order = 0;
	j = 0;
	if (!game->file_cont)
		return (0);
	while (game->file_cont[j])
	{
		if (element_chars(game->file_cont[j]))
		{
			prev_el_order = element_line_order(game->file_cont, j);
			if (prev_el_order && prev_el_order != 6)
			{
				next_el_order = element_line_order(game->file_cont, j + 1);
				if (next_el_order <= prev_el_order)
					return (0);
			}
		}
		j++;
	}
	return (1);
}

void	elements_placement(t_dpar *game)
{
	if (!check_elements_placement(game))
	{
		printf(B_R"Error:"RED" Elements out of order!\n"RES);
		free_map(game);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Valid elements placement!!!\n"RES);
}
