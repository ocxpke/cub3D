/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:47:22 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:25:41 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	valid_rgb(int num)
{
	if (num >= 0 && num <= 255)
		return (1);
	else
		return (0);
}

int	check_rgb(t_data *game)
{
	int	valid;

	valid = 0;
	if (valid_rgb(game->map_s->tex_col_s->cl_col_val->red))
		valid++;
	if (valid_rgb(game->map_s->tex_col_s->cl_col_val->green))
		valid++;
	if (valid_rgb(game->map_s->tex_col_s->cl_col_val->blue))
		valid++;
	if (valid_rgb(game->map_s->tex_col_s->fl_col_val->red))
		valid++;
	if (valid_rgb(game->map_s->tex_col_s->fl_col_val->green))
		valid++;
	if (valid_rgb(game->map_s->tex_col_s->fl_col_val->blue))
		valid++;
	if (valid == 6)
		return (1);
	else
		return (0);
}
