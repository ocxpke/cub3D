/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:54:42 by romorale          #+#    #+#             */
/*   Updated: 2026/04/21 20:33:29 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_key_count(char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'K')
				k++;
			i++;
		}
		j++;
	}
	return (k);
}

int	get_door_count(char **map)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	d = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'P')
				d++;
			i++;
		}
		j++;
	}
	return (d);
}

void	get_map_info(t_dpar *game)
{
	game->map_s->rows = get_rows(game->map_s->map);
	game->map_s->cols = get_cols(game->map_s->map);
	game->map_s->pstart_orientation = get_orientation(game->map_s->map);
	game->map_s->pstart_x = get_player_pos_col(game->map_s->map);
	game->map_s->pstart_y = get_player_pos_row(game->map_s->map);
	game->map_s->key_count = get_key_count(game->map_s->map);
	game->map_s->door_count = get_door_count(game->map_s->map);
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
			print_mapfile_map2(g->map_s->map[j][i]);
		}
		printf(MAG"]\n");
	}
}

void	print_mapfile( t_dpar *game)
{
	int	i;

	i = 0;
	printf(H_M"\n___________________file_content____________________\n\n"RES);
	print_mapfile_content(game);
	printf(H_M"\n_____________________elements______________________\n\n"RES);
	print_mapfile_tex(game);
	print_mapfile_colors(game);
	printf(H_M"\n_______________________info________________________\n\n"RES);
	print_mapfile_map_info(game);
	printf(H_M"\n________________________map________________________\n\n"RES);
	print_mapfile_map(game);
	printf(H_B"\nColumn\t\t");
	printf(MAG"["H_B"0"MAG"]<");
	while (i < game->map_s->cols - 6)
	{
		printf(MAG"-");
		i++;
	}
	printf(">["H_B"%d"MAG"]\n"RES, game->map_s->cols - 1);
	printf(H_M"\n________________________END________________________\n"RES);
}
