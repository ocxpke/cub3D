/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:47:35 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:16:03 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_num_val(char *line)
{
	int		i;
	int		len;
	char	*str;
	int		num;

	i = 0;
	len = 0;
	num = 0;
	while (line[len] && line[len] != ',')
		len++;
	str = malloc(len * sizeof(char) + 1);
	while (line[i] && line[i] != ',')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	if (str)
		num = ft_atoi(str);
	free(str);
	return (num);
}

int	get_num_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	return (i);
}

void	get_color_val_fl(t_data *game, char *line)
{
	int	coma;
	int	i;

	coma = 0;
	i = 2;
	while (line[i])
	{
		if (line[i] == ',')
		{
			coma++;
			i++;
		}
		if (coma == 0)
			game->map_s->tex_col_s->fl_col_val->red = get_num_val(&line[i]);
		else if (coma == 1)
			game->map_s->tex_col_s->fl_col_val->green = get_num_val(&line[i]);
		else if (coma == 2)
			game->map_s->tex_col_s->fl_col_val->blue = get_num_val(&line[i]);
		i += get_num_len(&line[i]);
	}
	return ;
}

void	get_color_val_cl(t_data *game, char *line)
{
	int	coma;
	int	i;

	coma = 0;
	i = 2;
	while (line[i])
	{
		if (line[i] == ',')
		{
			coma++;
			i++;
		}
		if (coma == 0)
			game->map_s->tex_col_s->cl_col_val->red = get_num_val(&line[i]);
		else if (coma == 1)
			game->map_s->tex_col_s->cl_col_val->green = get_num_val(&line[i]);
		else if (coma == 2)
			game->map_s->tex_col_s->cl_col_val->blue = get_num_val(&line[i]);
		i += get_num_len(&line[i]);
	}
	return ;
}
