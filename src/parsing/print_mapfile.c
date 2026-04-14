/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mapfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:23:12 by romorale          #+#    #+#             */
/*   Updated: 2026/04/14 16:49:05 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_mapfile_map_info( t_dpar *game)
{
	if (!game->map_s)
		return ;
	printf(H_B"Number of rows (x/height): \t");
	printf(MAG"["H_C"%d"MAG"]\n", game->map_s->rows);
	printf(H_B"Number of columns (y/width): \t");
	printf(MAG"["H_C"%d"MAG"]\n", game->map_s->cols);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"Player position (x/row): \t");
	printf(MAG"["H_C"%d"MAG"]\n", game->map_s->pstart_x);
	printf(H_B"Player position (y/column): \t");
	printf(MAG"["H_C"%d"MAG"]\n", game->map_s->pstart_y);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"Player orientation: \t\t");
	printf(MAG"["H_C"%c"MAG"]\n", game->map_s->pstart_orientation);
	printf(MAG"---------------------------------------------------\n");
}

void	print_mapfile_map( t_dpar *g)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (g->map_s->map[++j])
	{
		i = -1;
		printf(H_B"Row   "MAG"["H_B"%d"MAG"]\t[", j);
		while (g->map_s->map[j][++i])
		{
			if (g->map_s->map[j][i] == '1')
				printf(BHCYN"%c"RES, g->map_s->map[j][i]);
			else if (g->map_s->map[j][i] == '0')
				printf(BLU"%c"RES, g->map_s->map[j][i]);
			else if (g->map_s->map[j][i] == 'N' || g->map_s->map[j][i] == 'S'
				|| g->map_s->map[j][i] == 'W' || g->map_s->map[j][i] == 'E')
				printf(BHYEL"%c"RES, g->map_s->map[j][i]);
			else if (g->map_s->map[j][i] == ' ')
				printf(MAG"_"RES);
			else
				printf(H_C"%c"RES, g->map_s->map[j][i]);
		}
		printf(MAG"]\n");
	}
}

void	print_mapfile_colors( t_dpar *game)
{
	if (!game->map_s)
		return ;
	printf(H_B"floor color line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->fl_col);
	printf(H_B"floor color rgb:\t");
	printf(MAG"["H_R"%d"MAG"]", game->map_s->tex_col_s->fl_col_val->red);
	printf(MAG"["H_G"%d"MAG"]", game->map_s->tex_col_s->fl_col_val->green);
	printf(MAG"["H_B"%d"MAG"]\n", game->map_s->tex_col_s->fl_col_val->blue);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"ceiling color line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->cl_col);
	printf(H_B"ceiling color rgb:\t");
	printf(MAG"["H_R"%d"MAG"]", game->map_s->tex_col_s->cl_col_val->red);
	printf(MAG"["H_G"%d"MAG"]", game->map_s->tex_col_s->cl_col_val->green);
	printf(MAG"["H_B"%d"MAG"]\n", game->map_s->tex_col_s->cl_col_val->blue);
	printf(MAG"---------------------------------------------------\n");
}

void	print_mapfile_tex( t_dpar *game)
{
	if (!game->map_s)
		return ;
	printf(H_B"NO texture line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->no_tex);
	printf(H_B"SO texture path:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->no_tex_path);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"SO texture line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->so_tex);
	printf(H_B"SO texture path:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->so_tex_path);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"WE texture line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->we_tex);
	printf(H_B"WE texture path:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->we_tex_path);
	printf(MAG"---------------------------------------------------\n");
	printf(H_B"EA texture line:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->ea_tex);
	printf(H_B"EA texture path:\t");
	printf(MAG"["H_C"%s"MAG"]\n", game->map_s->tex_col_s->ea_tex_path);
	printf(MAG"---------------------------------------------------\n");
}

void	print_mapfile_content( t_dpar *game)
{
	int	i;

	i = 0;
	if (!game->file_cont[i])
		return ;
	while (game->file_cont[i])
	{
		if (!ft_strncmp(game->file_cont[i], "\n", 1))
			printf(H_B"line "MAG"["H_B"%d"MAG"]\t["MAG"\\n"MAG"]\n", i);
		else if (!ft_strncmp(game->file_cont[i], "\t", 1))
			printf(H_B"line "MAG"["H_B"%d"MAG"]\t["MAG"\\t"MAG"]\n", i);
		else
		{
			printf(H_B"line "MAG"["H_B"%d"MAG"]\t[", i);
			printf(H_C"%s"MAG"]\n", game->file_cont[i]);
		}
		i++;
	}
}
