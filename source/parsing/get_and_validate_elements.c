/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_validate_elements.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:39 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:32:22 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_elements(t_data *game)
{
	if (!get_textures(game, game->map_s->tex_col_s))
	{
		printf(B_R"Error:"RED" Unable to retrieve textures!\n"RES);
		return (0);
	}
	if (!get_f_c(game, game->map_s->tex_col_s))
	{
		printf(B_R"Error:"RED" Unable to retrieve colors!\n"RES);
		return (0);
	}
	if (!find_map(game))
	{
		printf(B_R"Error:"RED" Unable to retrieve map!\n"RES);
		return (0);
	}
	return (1);
}

int	validate_and_clean_elements(t_data *game)
{
	if (!valid_textures(game))
	{
		printf(B_R"Error:"RED" Textures are invalid!\n"RES);
		return (0);
	}
	if (!valid_f_c(game))
	{
		printf(B_R"Error:"RED" RGB colors are invalid!\n"RES);
		return (0);
	}
	return (1);
}
