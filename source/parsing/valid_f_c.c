/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_f_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:35:11 by romorale          #+#    #+#             */
/*   Updated: 2026/04/08 20:34:35 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	count_values(char *line)
{
	int	i;
	int	d;

	i = 2;
	d = 0;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return (0);
	while (!(line[i] >= '0' && line[i] <= '9'))
		i++;
	if (i > 2)
		return (0);
	while (line[i])
	{
		if ((line[i] == ',') && (line[i - 1] >= '0' && line[i - 1] <= '9')
			&& (line[i + 1] >= '0' && line[i + 1] <= '9'))
			d++;
		i++;
	}
	if (d == 2)
		return (1);
	return (0);
}

int	count_comas(char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] == ',')
			c++;
		i++;
	}
	if (c == 2)
		return (1);
	return (0);
}

int	valid_color(char *line)
{
	int	comas;
	int	i;
	int	val_len;

	comas = 0;
	i = 2;
	val_len = 0;
	if (!line)
		return (0);
	if (line[1] != ' ')
		return (0);
	if (!count_comas(line) || !count_values(line))
		return (0);
	while (line[i] && line[i] != ',' && line[i + 1])
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		if (line[i] >= '0' && line[i] <= '9')
			val_len++;
		i++;
	}
	if (val_len > 3)
		return (0);
	return (1);
}

int	valid_f_c(t_data *game)
{
	int	valid;

	valid = 0;
	if (valid_color(game->map_s->tex_col_s->fl_col))
	{
		get_color_val_fl(game, game->map_s->tex_col_s->fl_col);
		valid++;
	}
	if (valid_color(game->map_s->tex_col_s->cl_col))
	{
		get_color_val_cl(game, game->map_s->tex_col_s->cl_col);
		valid++;
	}
	valid += check_rgb(game);
	if (valid == 3)
		return (1);
	else
		return (0);
}
