/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_check_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:39 by romorale          #+#    #+#             */
/*   Updated: 2026/04/07 20:02:25 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	open_a_tex(t_data *game, int step)
{
	int	fd;

	fd = -1;
	if (step == 1)
		fd = open(game->map_s->tex_col_s->no_tex_path, O_RDONLY);
	if (step == 2)
		fd = open(game->map_s->tex_col_s->so_tex_path, O_RDONLY);
	if (step == 3)
		fd = open(game->map_s->tex_col_s->we_tex_path, O_RDONLY);
	if (step == 4)
		fd = open(game->map_s->tex_col_s->ea_tex_path, O_RDONLY);
	return (fd);
}

int	validate_tex_paths(t_data *game)
{
	int	step;
	int	fd;

	fd = -1;
	step = 1;
	if (game->map_s->tex_col_s)
	{
		while (step < 5)
		{
			fd = open_a_tex(game, step);
			if (fd == -1)
				return (0);
			close(fd);
			step++;
		}
		if (step == 5)
			return (1);
	}
	return (0);
}

void	open_and_check_textures(t_data *game)
{
	if (!validate_tex_paths(game))
	{
		printf(B_R"Error:"RED" Texture/s not found at path!\n"RES);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" All textures opened successfully!!!\n"RES);
}
