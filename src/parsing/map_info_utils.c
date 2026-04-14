/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:54:42 by romorale          #+#    #+#             */
/*   Updated: 2026/04/08 18:46:34 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_map_info(t_dpar *game)
{
	game->map_s->rows = get_rows(game->map_s->map);
	game->map_s->cols = get_cols(game->map_s->map);
	game->map_s->pstart_orientation = get_orientation(game->map_s->map);
	game->map_s->pstart_x = get_player_pos_row(game->map_s->map);
	game->map_s->pstart_y = get_player_pos_col(game->map_s->map);
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
