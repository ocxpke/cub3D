/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:38:41 by romorale          #+#    #+#             */
/*   Updated: 2026/05/19 15:53:13 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_tex_chars(char *s)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (!s || !s[2])
		return (0);
	while (s[i])
	{
		if (s[i] == 32)
			space++;
		i++;
	}
	if (space > 1)
		return (0);
	return (1);
}

void	find_tex_path(t_dpar *game, char *line)
{
	int i;

	i = 2;
	while (line[i] == 32)
		i++;
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		game->map_s->tex_col_s->no_tex_path
			= ft_strdup(&game->map_s->tex_col_s->no_tex[i]);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		game->map_s->tex_col_s->so_tex_path
			= ft_strdup(&game->map_s->tex_col_s->so_tex[i]);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		game->map_s->tex_col_s->we_tex_path
			= ft_strdup(&game->map_s->tex_col_s->we_tex[i]);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		game->map_s->tex_col_s->ea_tex_path
			= ft_strdup(&game->map_s->tex_col_s->ea_tex[i]);
}

int	check_textures(t_dpar *game)
{
	if (check_path_ext(game->map_s->tex_col_s->no_tex))
		find_tex_path(game, game->map_s->tex_col_s->no_tex);
	else
		return (0);
	if (check_path_ext(game->map_s->tex_col_s->so_tex))
		find_tex_path(game, game->map_s->tex_col_s->so_tex);
	else
		return (0);
	if (check_path_ext(game->map_s->tex_col_s->we_tex))
		find_tex_path(game, game->map_s->tex_col_s->we_tex);
	else
		return (0);
	if (check_path_ext(game->map_s->tex_col_s->ea_tex))
		find_tex_path(game, game->map_s->tex_col_s->ea_tex);
	else
		return (0);
	return (1);
}

int	valid_textures(t_dpar *game)
{
	int	valid;

	valid = check_textures(game);
	if (valid)
		return (1);
	else
		return (0);
}
