/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_and_f_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:35:35 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:16:57 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_a_tex(char *str, t_tex_col *tex_col_s)
{
	if (str[0] == 'N')
		tex_col_s->no_tex = ft_strdup(str);
	else if (str[0] == 'S')
		tex_col_s->so_tex = ft_strdup(str);
	else if (str[0] == 'W')
		tex_col_s->we_tex = ft_strdup(str);
	else if (str[0] == 'E')
		tex_col_s->ea_tex = ft_strdup(str);
	else
		return ;
}

int	get_textures(t_dpar *game, t_tex_col *tex_col_s)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (game->file_cont[i])
	{
		if ((game->file_cont[i][0] == 'N' && game->file_cont[i][1] == 'O')
			|| (game->file_cont[i][0] == 'S' && game->file_cont[i][1] == 'O')
			|| (game->file_cont[i][0] == 'W' && game->file_cont[i][1] == 'E')
			|| (game->file_cont[i][0] == 'E' && game->file_cont[i][1] == 'A'))
		{
			get_a_tex(game->file_cont[i], tex_col_s);
			flags++;
		}
		i++;
	}
	if (flags == 4)
		return (1);
	else
		return (0);
}

void	get_a_col(char *str, t_tex_col *tex_col_s)
{
	if (str[0] == 'F')
		tex_col_s->fl_col = ft_strdup(str);
	else if (str[0] == 'C')
		tex_col_s->cl_col = ft_strdup(str);
	else
		return ;
}

int	get_f_c(t_dpar *game, t_tex_col *tex_col_s)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (game->file_cont[i])
	{
		if (game->file_cont[i][0] == 'F' || game->file_cont[i][0] == 'C')
		{
			get_a_col(game->file_cont[i], tex_col_s);
			flags++;
		}
		i++;
	}
	if (flags == 2)
		return (1);
	else
		return (0);
}
